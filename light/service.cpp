/*
 * Copyright (C) 2018 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "android.hardware.light@2.0-service.aura"

#include <android-base/logging.h>
#include <hidl/HidlTransportSupport.h>

#include "Light.h"

using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;

using android::hardware::light::V2_0::ILight;
using android::hardware::light::V2_0::implementation::Light;

using android::OK;
using android::sp;
using android::status_t;

int main() {
    status_t status;
    sp<ILight> service = nullptr;

    LOG(INFO) << "Light HAL service 2.0 is starting.";

    service = new Light();
    if (service == nullptr) {
        LOG(ERROR) << "Can not create an instance of Light HAL Iface, exiting.";
        goto shutdown;
    }

    configureRpcThreadpool(1, true /*callerWillJoin*/);

    status = service->registerAsService();
    if (status != OK) {
        LOG(ERROR) << "Could not register service for Light HAL Iface (" << status << ")";
        goto shutdown;
    }

    LOG(INFO) << "Light HAL service is ready.";
    joinRpcThreadpool();
    // Should not pass this line

shutdown:
    // In normal operation, we don't expect the thread pool to exit
    LOG(ERROR) << "Light HAL service is shutting down.";
    return 1;
}
