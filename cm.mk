#
# Copyright (C) 2015 The CyanogenMod Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

$(call inherit-product, device/htc/b2wlj/full_b2wlj.mk)

# Inherit some common CM stuff.
$(call inherit-product, vendor/cm/config/common_full_phone.mk)

PRODUCT_NAME := cm_b2wlj

PRODUCT_BUILD_PROP_OVERRIDES += \
    BUILD_FINGERPRINT="htc/HTL23_jp_kdi/htc_b2wlj:4.4.4/KTU84P/515340.5:user/release-keys" \
    PRIVATE_BUILD_DESC="2.14.970.5 CL515340 release-keys"
