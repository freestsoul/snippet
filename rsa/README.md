密钥长度选用：2048，rsa填充方式使用：OPENSSL_PKCS1_PADDING
生成私钥文件：
openssl genrsa -out rsa_pri_key_2048.pem 2048
利用私钥，生成公钥：
openssl rsa -in rsa_pri_key_2048.pem -pubout -out rsa_pub_key_2048.pem

注意:
	1. rsa加密的明文不能超过密钥的长度（117字节），超过的要分段加密，拼接后传输
	2. 加密后的字符串是二进制字符串，需要base64_encode编码，再http传输
效率：
      1. 500个utf-8字符，php解密需要50ms左右，加密很快5ms 
      2. c++ 加密，解密都很快, 加密 1ms左右, 解密 2ms左右