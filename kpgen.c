#include <node_api.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "kp_gen.h"

// char localcredential[] =
//         "{\"privateKey\":\"2f882b550c93246fddd48bd794b8b6d2aeec1902b07ee23c8883f726211d0057\",\"success\":true,"
//         "\"deviceCertificate\":{\"certIssuer\":\"OPENAPI\",\"companyCode\":\"2021003177621036\",\"deviceInformation\":{"
//         "\"deviceImei\":\"deviceImei\",\"deviceMac\":\"deviceMac\",\"deviceSn\":\"acfdaa8a7d0d42c9afd31cef77aa99c0\"},"
//         "\"extraParams\":{\"features\":[\"ANT_FORREST\",\"TRANSPORT\",\"PAYMENT\"]},\"productModel\":\"LX100\","
//         "\"productType\":\"WATCH\",\"publicKey\":\"-----BEGIN PUBLIC "
//         "KEY-----\\nMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAE1k/"
//         "ocE6VIhnfO0OyJeNaNBN5pxLG\\na2RCs8Rugis606UAnPd+JT290XYHb6xEUBIa7zBRxvTtMI6SoJOpVQpDQg==\\n-----END PUBLIC "
//         "KEY-----\\n\",\"securityNegotiation\":\"ECDH\",\"sign\":\"cYexPW2mvmgTmEpuULuUGJK8VpLgQ+cRIlGwcYt1TL0RvAxvVSF/"
//         "B8dAz+schO51CQs7FAcM3dndD+EzNDpxFZB1k1iW3nhMPSHdPKysufa84xut7dplL4DoUT8rn/YTGih3mKzsSZb+7Jhm6GGuz9Pu3JcpeBpJJ/"
//         "NbOA62rZemDeOl7xVB0KBXeSumZq8Us8OV4uvfHZ0UQEn83dwSqrSdbsRmrfR4gv5zQhlpJPRAkm0BQdLbYJGks9tbSTSNuiB68gZDZJT3BL++"
//         "JfMm2/"
//         "yE32RcdAIIJRwHIV3Yer9b4rcgz+22LT9E2EGDYjGMemlN7EiR+5OO0iIPLsWhsw==\",\"signAlgorithm\":\"BASE64_OVER_"
//         "RSA2048\",\"sn\":\"2023102015024022836516\"}}";

napi_value  CsiGenKeyWrapper(napi_env env, napi_callback_info info) {
  size_t argc = 4;
  napi_value args[4];
  napi_get_cb_info(env, info, &argc, args, NULL, NULL);

  // 获取cid字符串参数
  size_t cid_size;
  napi_get_value_string_utf8(env, args[0], NULL, 0, &cid_size);
  char* cid = (char*)malloc(cid_size + 1);
  napi_get_value_string_utf8(env, args[0], cid, cid_size + 1, NULL);

  // 获取huk字符串参数
  size_t huk_len;
  napi_get_value_string_utf8(env, args[1], NULL, 0, &huk_len);
  char* huk = (char*)malloc(huk_len + 1);
  napi_get_value_string_utf8(env, args[1], huk, huk_len + 1, NULL);

    // 获取huk字符串参数
  size_t credential_len;
  napi_get_value_string_utf8(env, args[2], NULL, 0, &credential_len);
  char*  credential = (char*)malloc(credential_len + 1);
  napi_get_value_string_utf8(env, args[2], credential, credential_len + 1, NULL);


  int isnew;
  napi_get_value_int32(env, args[3], &isnew);

  // 调用 csi_generate_key_provision
  char* kp = csi_generate_key_provision(cid,huk,credential,isnew);


  napi_value result;
  if(kp != NULL && kp[0]){
    // 创建并返回结果字符串
    napi_create_string_utf8(env, kp, NAPI_AUTO_LENGTH, &result);

  }else{
    napi_create_string_utf8(env, "csi error", NAPI_AUTO_LENGTH, &result);
  }

  // // 创建并返回结果字符串
  // napi_value result;
  // napi_create_string_utf8(env, dest, NAPI_AUTO_LENGTH, &result);

  free(cid);
  free(huk);
  free(credential);
  return result;
}

napi_value Init(napi_env env, napi_value exports) {
  napi_status status;
  napi_value fn;

  status = napi_create_function(env, NULL, 0,  CsiGenKeyWrapper, NULL, &fn);
  if (status != napi_ok) return NULL;

  status = napi_set_named_property(env, exports, "csigenkey", fn);
  if (status != napi_ok) return NULL;

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)

