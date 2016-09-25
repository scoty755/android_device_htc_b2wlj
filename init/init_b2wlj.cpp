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

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

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
    char platform[PROP_VALUE_MAX];
    char bootmid[PROP_VALUE_MAX];
    char device[PROP_VALUE_MAX];
    int rc;

    rc = property_get("ro.board.platform", platform);
    if (!rc || strncmp(platform, ANDROID_TARGET, PROP_VALUE_MAX))
        return;

    property_get("ro.boot.mid", bootmid);

    if (strstr(bootmid, "0PAG10000")) {
        /* b2wlj */
        common_properties();
        cdma_properties("0", "10");
        property_set("ro.product.model", "HTL23");
        property_set("ro.build.fingerprint", "htc/HTL23_jp_kdi/htc_b2wlj:4.4.2/KOT49H/368778.1:user/release-keys");
        property_set("ro.build.description", "1.17.970.1 CL368778 release-keys");
        property_set("ro.product.device", "htc_b2wlj");
        property_set("ro.build.product", "htc_b2wlj");
        property_set("ro.ril.oem.ecclist", "110,118,119,184110,184118,184119,186110,186118,186119");
        property_set("ro.ril.enable.sdr", "0");
        property_set("ro.ril.enable.r8fd", "0");
        property_set("ro.ril.enable.pre_r8fd", "0");
        property_set("ro.ril.disable.fd.plmn.prefix", "23402,23410,23411,23420");
        property_set("ro.ril.set.mtusize", "1420");
        property_set("ro.ril.air.enabled", "1");
        property_set("ro.ril.wp.feature", "1");
        property_set("ro.cdma.data_retry_config", "max_retries=infinite,26000,52000,104000,208000,416000,832000,1664000,1800000");
        property_set("ro.gsm.data_retry_config", "max_retries=infinite,26000,52000,104000,208000,416000,832000,1664000,1800000");
        property_set("ro.gsm.2nd_data_retry_config", "max_retries=infinite,26000,52000,104000,208000,416000,832000,1664000,1800000");
        property_set("ro.ril.gsm.to.lte.blind.redir", "1");
        property_set("ro.config.svlte1x", "true");
        property_set("ro.ril.def.agps.mode", "6");
        property_set("ro.telephony.get_imsi_from_sim", "true");
    } else {
        /* b2ul */
        common_properties();
        gsm_properties("9");
        property_set("ro.product.model", "HTC Butterfly 2");
        property_set("ro.build.fingerprint", "htc/htc_asia_wwe/htc_b2ul:4.4.4/KTU84P/421314.5:user/release-keys");
        property_set("ro.build.description", "2.07.707.5 CL421314 release-keys");
        property_set("ro.product.device", "htc_b2ul");
    }

    property_get("ro.product.device", device);
    ERROR("Found bootmid %s setting build properties for %s device\n", bootmid, device);
}
