#include "ipclass.h"
#include "entrypoint.h"
#include <geolite2pp/GeoLite2PP.hpp>
#include <swiftly-ext/files.h>
#include <string>

GeoLite2PP::DB* maxminddbCity = nullptr;
GeoLite2PP::DB* maxminddbASN = nullptr;

void SetupScripting(EContext* ctx)
{
    if (!maxminddbCity) maxminddbCity = new GeoLite2PP::DB(GeneratePath("addons/swiftly/data/GeoLite2-City.mmdb"));
    if (!maxminddbASN) maxminddbASN = new GeoLite2PP::DB(GeneratePath("addons/swiftly/data/GeoLite2-ASN.mmdb"));

    ADD_CLASS("IPAPI");

    ADD_CLASS_FUNCTION("IPAPI", "IPAPI", [](FunctionContext* context, ClassData* data) -> void {});

    ADD_CLASS_FUNCTION("IPAPI", "GetIsoCode", [](FunctionContext* context, ClassData* data) -> void {
        std::string ip = context->GetArgumentOr<std::string>(0, "0.0.0.0");
        try {
            auto m = maxminddbCity->get_all_fields(ip);
            context->SetReturn(m["country_iso_code"]);
        }
        catch (std::exception& e) {
            context->SetReturn("");
        }
        });

    ADD_CLASS_FUNCTION("IPAPI", "GetContinent", [](FunctionContext* context, ClassData* data) -> void {
        std::string ip = context->GetArgumentOr<std::string>(0, "0.0.0.0");
        try {
            auto m = maxminddbCity->get_all_fields(ip);
            context->SetReturn(m["continent"]);
        }
        catch (std::exception& e) {
            context->SetReturn("");
        }
        });

    ADD_CLASS_FUNCTION("IPAPI", "GetCountry", [](FunctionContext* context, ClassData* data) -> void {
        std::string ip = context->GetArgumentOr<std::string>(0, "0.0.0.0");
        try {
            auto m = maxminddbCity->get_all_fields(ip);
            context->SetReturn(m["country"]);
        }
        catch (std::exception& e) {
            context->SetReturn("");
        }
        });

    ADD_CLASS_FUNCTION("IPAPI", "GetRegion", [](FunctionContext* context, ClassData* data) -> void {
        std::string ip = context->GetArgumentOr<std::string>(0, "0.0.0.0");
        try {
            auto m = maxminddbCity->get_all_fields(ip);
            context->SetReturn(m["subdivision"]);
        }
        catch (std::exception& e) {
            context->SetReturn("");
        }
        });

    ADD_CLASS_FUNCTION("IPAPI", "GetCity", [](FunctionContext* context, ClassData* data) -> void {
        std::string ip = context->GetArgumentOr<std::string>(0, "0.0.0.0");
        try {
            auto m = maxminddbCity->get_all_fields(ip);
            context->SetReturn(m["city"]);
        }
        catch (std::exception& e) {
            context->SetReturn("");
        }
        });

    ADD_CLASS_FUNCTION("IPAPI", "GetTimezone", [](FunctionContext* context, ClassData* data) -> void {
        std::string ip = context->GetArgumentOr<std::string>(0, "0.0.0.0");
        try {
            auto m = maxminddbCity->get_all_fields(ip);
            context->SetReturn(m["time_zone"]);
        }
        catch (std::exception& e) {
            context->SetReturn("");
        }
        });

    ADD_CLASS_FUNCTION("IPAPI", "GetLatitude", [](FunctionContext* context, ClassData* data) -> void {
        std::string ip = context->GetArgumentOr<std::string>(0, "0.0.0.0");
        try {
            auto m = maxminddbCity->get_all_fields(ip);
            context->SetReturn(V_StringToFloat32(m["latitude"].c_str(), 0.0f));
        }
        catch (std::exception& e) {
            context->SetReturn(0.0f);
        }
        });

    ADD_CLASS_FUNCTION("IPAPI", "GetLongitude", [](FunctionContext* context, ClassData* data) -> void {
        std::string ip = context->GetArgumentOr<std::string>(0, "0.0.0.0");
        try {
            auto m = maxminddbCity->get_all_fields(ip);
            context->SetReturn(V_StringToFloat32(m["longitude"].c_str(), 0.0f));
        }
        catch (std::exception& e) {
            context->SetReturn(0.0f);
        }
        });

    ADD_CLASS_FUNCTION("IPAPI", "GetASN", [](FunctionContext* context, ClassData* data) -> void {
        std::string ip = context->GetArgumentOr<std::string>(0, "0.0.0.0");
        try {
            auto lookupRes = maxminddbASN->get_field(ip, "en", GeoLite2PP::VCStr{ "autonomous_system_number", nullptr });
            context->SetReturn(lookupRes);
        }
        catch (std::exception& e) {
            context->SetReturn("");
        }
        });

    ADD_VARIABLE("_G", "ip", MAKE_CLASS_INSTANCE_CTX(ctx, "IPAPI", {}));
}