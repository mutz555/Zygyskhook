#pragma once

class Api {
public:
    void set_option(int option) {}
    };

    class AppSpecializeArgs {};
    class ServerSpecializeArgs {};

    class ApiManager {
    public:
        static Api* get_api() {
                static Api instance;
                        return &instance;
                            }
                            };