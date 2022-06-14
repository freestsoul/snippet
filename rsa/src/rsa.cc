/**************************************************************************

Copyright: freestsoul

Author: freesoul

Date: 2022-06-14

Description: Provide RSA Encode and Decode function.

**************************************************************************/

#include <iostream>
#include <vector>
#include <ctime>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include "base64.h"
#include "rsa.h"

namespace com {
namespace freesoul {
namespace snippet {
/* rsa密钥长度1024, 最多加密 1024 / 8 = 128
#define BASE_ENCODE_LEN 128
// RSA_PKCS1_PADDING建议的padding就占用了11个字节
// 这个值必须小于 117 （ 128 - 11 = 117）， 11表示RSA_PKCS1_PADDING建议的padding
#define RSA_ENC_LEN 100
// base64_encode的encode的长度是和原文长度有个计算公式：
// $len2 = $len1 % 3 > 0 ? (floor($len1 / 3) * 4 + 4) : ($len1 * 4 / 3);
// 128个字节base64_encode后的长度固定是172
#define RSA_DEC_LEN 172
*/

// rsa密钥长度2048, 最多加密 2048 / 8 = 128
#define BASE_ENCODE_LEN 256
// RSA_PKCS1_PADDING建议的padding就占用了11个字节
// 这个值必须小于 245 （ 256 - 11 = 245）， 11表示RSA_PKCS1_PADDING建议的padding
#define RSA_ENC_LEN 245
// base64_encode的encode的长度是和原文长度有个计算公式：
// $len2 = $len1 % 3 > 0 ? (floor($len1 / 3) * 4 + 4) : ($len1 * 4 / 3);
// 256个字节base64_encode后的长度固定是344
#define RSA_DEC_LEN 344

/*
 * 按len长度将输入str分拆成多个string到vector中。
 */
std::vector<std::string> split_str_to_vec(const std::string& str, int len) {
    std::vector<std::string> v;
    int pos = 0;
    std::string tmp;
    while (pos < str.size()) {
        tmp = str.substr(pos, len);
        if (!tmp.empty()) {
            v.emplace_back(std::move(tmp));
            pos += len;
        }
    }
    return v;
}

// ras encode implement.
std::string rsa_encode(const std::string& public_pem_file,
                       const std::string& plaintext) {
    if (public_pem_file.empty() || plaintext.empty()) {
        assert(false);
        return "";
    }
    // split plaintext string -> vector
    std::vector<std::string> v;
    v = split_str_to_vec(plaintext, RSA_ENC_LEN);
    if (v.empty()) {
        return "";
    }
    FILE* pub_key_file = fopen(public_pem_file.c_str(), "rb");
    if (pub_key_file == NULL) {
        assert(false);
        return "";
    }
    std::string str_ret;
    std::string str_res;
    RSA* rsa_public_key = RSA_new();
    if (PEM_read_RSA_PUBKEY(pub_key_file, &rsa_public_key, 0, 0) == NULL) {
        assert(false);
        return "";
    }
    int rsa_len = RSA_size(rsa_public_key);
    char* encode_buff = new char[rsa_len];
    for (int i = 0; i < v.size(); i++) {
        // std::cout << "vector i: "<< i << " data:" << v[i] << std::endl;
        int ret = RSA_public_encrypt(
            v[i].length(), (const unsigned char*)v[i].c_str(),
            (unsigned char*)encode_buff, rsa_public_key, RSA_PKCS1_PADDING);
        // std::cout << "rsa_enc_str: " << encode_buff << std::endl;
        if (ret >= 0) {
            str_ret = base64_encode((const unsigned char*)encode_buff,
                                    BASE_ENCODE_LEN);
            str_res.append(str_ret);
        }
    }

    delete[] encode_buff;
    RSA_free(rsa_public_key);
    fclose(pub_key_file);
    CRYPTO_cleanup_all_ex_data();

    return str_res;
}

// ras decode implement.
std::string rsa_decode(const std::string& private_pem_file,
                       const std::string& ciphertext) {
    if (private_pem_file.empty() || ciphertext.empty()) {
        assert(false);
        return "";
    }
    FILE* pri_key_file = fopen(private_pem_file.c_str(), "rb");
    if (pri_key_file == NULL) {
        assert(false);
        return "";
    }
    std::string str_ret;
    std::string str_res;
    RSA* rsa_private_key = RSA_new();
    if (PEM_read_RSAPrivateKey(pri_key_file, &rsa_private_key, 0, 0) == NULL) {
        assert(false);
        return "";
    }
    // string -> vector
    std::vector<std::string> v;
    v = split_str_to_vec(ciphertext, RSA_DEC_LEN);
    if (v.empty()) {
        return "";
    }
    int rsa_len = RSA_size(rsa_private_key);
    char* decode_buff = new char[rsa_len];
    for (int i = 0; i < v.size(); i++) {
        str_ret = base64_decode(v[i]);
        int ret = RSA_private_decrypt(
            str_ret.length(), (const unsigned char*)str_ret.c_str(),
            (unsigned char*)decode_buff, rsa_private_key, RSA_PKCS1_PADDING);
        if (ret >= 0) {
            str_ret = std::string((char*)decode_buff, ret);
            str_res.append(str_ret);
        }
    }

    delete[] decode_buff;
    RSA_free(rsa_private_key);
    fclose(pri_key_file);
    CRYPTO_cleanup_all_ex_data();

    return str_res;
}
}  // namespace snippet
}  // namespace freesoul
}  // namespace com

/*
 * compile comand:
 *   g++ rsa.cc base64.cc -std=c++17 -I/opt/homebrew/opt/openssl/include -L/opt/homebrew/opt/openssl/lib -lssl -lcrypto -lpthread -ldl -o rsa
 */
int main() {
    time_t begin, end;
    //原文
    const std::string one =
        "{\"worlds\":\"你好世界，加入我们的大家庭。卫星3243243243242432，>>>>>>"
        ">>>.....。。。。。。。。。。。"
        "。。。。。。。。。买车，买车二手车文你好你好世界，加入我们的大家庭。卫"
        "星3243243243242432，>>>>>>>>>.....。。。。。。。。。。。。。。"
        "。。。。。。买车，买车二手车文你好你好世界，加入我们的大家庭。卫星3243"
        "243243242432，>>>>>>>>>.....。。。。。。。。。。。。。。。。。。"
        "。。买车，买车二手车文你好 "
        "你好世界，加入我们的大家庭。卫星3243243243242432，>>>>>>>>>....."
        "。。。。。。。。。。。。。。。。。。。。买车，"
        "买车二手车文你好你好世界，加入我们的大家庭。卫星3243243243242432，>>>>"
        ">>>>>....."
        "。。。。。。。。。。。。。。。。。。。。买车，买车二手车文你好\"}";
    std::cout << "原文: " << one << std::endl;
    begin = clock();
    //密文（base64数据）
    std::string two =
        com::freesoul::snippet::rsa_encode("rsa_pub_key_2048.pem", one);
    end = clock();
    std::cout << "密文: " << two << std::endl;
    std::cout << "encTime: " << double(end - begin) / CLOCKS_PER_SEC * 1000
              << " ms" << std::endl;

    begin = clock();
    //名文
    std::string three =
        com::freesoul::snippet::rsa_decode("rsa_pri_key_2048.pem", two);
    end = clock();
    std::cout << "明文: " << three << std::endl;
    std::cout << "decTime: " << double(end - begin) / CLOCKS_PER_SEC * 1000
              << " ms" << std::endl;
    return 0;
}