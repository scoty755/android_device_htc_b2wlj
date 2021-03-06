/*
   Copyright (c) 2013, The Linux Foundation. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include <android-base/properties.h>
#include <android-base/logging.h>

#include "property_service.h"
#include "vendor_init.h"

using android::base::GetProperty;
using android::init::property_set;

void property_override(char const prop[], char const value[])
{
    prop_info *pi;

    pi = (prop_info*) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void property_override_dual(char const system_prop[], char const vendor_prop[], char const value[])
{
    property_override(system_prop, value);
    property_override(vendor_prop, value);
}

void common_properties()
{
    property_set("rild.libargs", "-d /dev/smd0");
    property_set("ro.ril.hsdpa.category", "14");
    property_set("ro.ril.hsxpa", "4");
    property_set("ro.ril.disable.cpc", "1");
}

void cdma_properties(char const default_cdma_sub[], char const default_network[])
{
    property_set("ro.telephony.default_cdma_sub", default_cdma_sub);
    property_set("ro.telephony.default_network", default_network);
    property_set("telephony.lteOnCdmaDevice", "1");
    property_set("ro.ril.enable.sdr", "0");
    property_set("persist.radio.snapshot_enabled", "1");
    property_set("persist.radio.snapshot_timer", "22");
}

void gsm_properties(char const default_network[])
{
    property_set("ro.telephony.default_network", default_network);
    property_set("telephony.lteOnGsmDevice", "1");
    property_set("ro.ril.radio.svn", "1");
}

void vendor_load_properties()
{
    std::string platform;
    std::string bootmid;
    std::string device;

    platform = GetProperty("ro.board.platform", "");
    if (platform != ANDROID_TARGET)
        return;

    bootmid = GetProperty("ro.boot.mid", "");

    if (bootmid == "0PAG10000") {
        /* b2wlj */
        common_properties();
        cdma_properties("0", "10");
        property_override("ro.product.model", "HTL23");
        property_override("ro.build.fingerprint", "htc/HTL23_jp_kdi/htc_b2wlj:4.4.2/KOT49H/368778.1:user/release-keys");
        property_override("ro.build.description", "1.17.970.1 CL368778 release-keys");
        property_override("ro.product.device", "htc_b2wlj");
        property_override("ro.build.product", "htc_b2wlj");
        property_override("ro.ril.oem.ecclist", "110,118,119,184110,184118,184119,186110,186118,186119");
        property_override("ro.ril.enable.sdr", "0");
        property_override("ro.ril.enable.r8fd", "0");
        property_override("ro.ril.enable.pre_r8fd", "0");
        property_override("ro.ril.disable.fd.plmn.prefix", "23402,23410,23411,23420");
        property_override("ro.ril.set.mtusize", "1420");
        property_override("ro.ril.air.enabled", "1");
        property_override("ro.ril.wp.feature", "1");
        property_override("ro.cdma.data_retry_config", "max_retries=infinite,26000,52000,104000,208000,416000,832000,1664000,1800000");
        property_override("ro.gsm.data_retry_config", "max_retries=infinite,26000,52000,104000,208000,416000,832000,1664000,1800000");
        property_override("ro.gsm.2nd_data_retry_config", "max_retries=infinite,26000,52000,104000,208000,416000,832000,1664000,1800000");
        property_override("ro.ril.gsm.to.lte.blind.redir", "1");
        property_override("ro.config.svlte1x", "true");
        property_override("ro.ril.def.agps.mode", "6");
        property_override("ro.telephony.get_imsi_from_sim", "true");
    } else {
        /* b2ul */
        common_properties();
        gsm_properties("9");
        property_override("ro.product.model", "HTC Butterfly 2");
        property_override("ro.build.fingerprint", "htc/htc_asia_wwe/htc_b2ul:4.4.4/KTU84P/421314.5:user/release-keys");
        property_override("ro.build.description", "2.07.707.5 CL421314 release-keys");
        property_override("ro.product.device", "htc_b2ul");
    }

    device = GetProperty("ro.product.device", "");
    LOG(ERROR) << "Found bootmid '" << bootmid.c_str() << "' setting build properties for '" << device.c_str() << "' device\n";
}
