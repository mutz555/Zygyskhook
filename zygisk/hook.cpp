// Full JNI-based Zygisk module to bypass isHardwareDetected()
// This version uses Dobby for inline native hook

#include <jni.h>
#include <unistd.h>
#include <android/log.h>
#include <zygisk.hpp>
#include <dobby.h>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "ZygiskFP", __VA_ARGS__)

// Original method pointer
typedef jboolean (*isHardwareDetected_t)(JNIEnv *, jobject);
isHardwareDetected_t orig_isHardwareDetected = nullptr;

// Replacement method
jboolean hooked_isHardwareDetected(JNIEnv *env, jobject thiz) {
    LOGI("[+] isHardwareDetected() hooked! Returning true");
    return JNI_TRUE;
}

class FingerprintBypass : public zygisk::ModuleBase {
public:
    void onLoad(zygisk::Api *api, JNIEnv *env) override {
        api->setOption(zygisk::DLCLOSE_MODULE_LIBRARY);
        LOGI("[+] Zygisk module loaded with Dobby inline hook");
    }

    void postAppSpecialize(zygisk::AppSpecializeArgs *args, JNIEnv *env) override {
        jclass cls = env->FindClass("com/android/server/biometrics/sensors/fingerprint/FingerprintServiceStubImpl");
        if (!cls) {
            LOGI("[-] Cannot find FingerprintServiceStubImpl class");
            return;
        }

        jmethodID method = env->GetMethodID(cls, "isHardwareDetected", "()Z");
        if (!method) {
            LOGI("[-] Cannot find isHardwareDetected() method");
            return;
        }

        void *addr = reinterpret_cast<void *>(method);
        if (DobbyHook(addr, (void *)hooked_isHardwareDetected, (void **)&orig_isHardwareDetected) == RS_SUCCESS) {
            LOGI("[+] isHardwareDetected() hooked successfully");
        } else {
            LOGI("[-] Failed to hook isHardwareDetected()");
        }
    }
};

REGISTER_ZYGISK_MODULE(FingerprintBypass)
