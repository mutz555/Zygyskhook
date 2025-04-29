#include <jni.h>
#include <android/log.h>
#include <zygisk.hpp>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "ZygiskFP", __VA_ARGS__)

class FingerprintBypass : public zygisk::ModuleBase {
public:
    void onLoad(zygisk::Api *api, JNIEnv *env) override {
        api->setOption(zygisk::DLCLOSE_MODULE_LIBRARY);
        LOGI("[+] Zygisk module loaded (no Dobby)");
    }

    void postAppSpecialize(zygisk::AppSpecializeArgs *args, JNIEnv *env) override {
        LOGI("[+] postAppSpecialize() called (no fingerprint bypass yet)");
    }
};

REGISTER_ZYGISK_MODULE(FingerprintBypass)
