Chatting programm using PQC TLS
===

### Prerequisite
```
sudo apt install cmake gcc libtool libssl-dev make ninja-build git qt5-default qt5-qmake
```

### Git clone
```
git clone --branch main https://github.com/open-quantum-safe/liboqs.git
git clone https://github.com/open-quantum-safe/openssl.git
git clone git@github.com:pqcy/pqc-app.git
```

### Build oqs
```
cd liboqs
mkdir build && cd build
cmake -GNinja -DCMAKE_INSTALL_PREFIX=../../openssl/oqs ..
ninja
ninja install
cd ../..
```

### Build openssl
```
cd openssl
./config --debug
make -j
cd ..
```

### Install header and library files
```
cp openssl/lib*.so* pqc-app/lib/
cp -r openssl/include/crypto pqc-app/include/
cp -r openssl/include/openssl pqc-app/include/
cp -r openssl/include/internal pqc-app/include/
cp -r openssl/oqs/include/oqs/ pqc-app/include/
```
### Make and apply a SPHINCS+ PEM File
```
cd openssl
apps/openssl req -x509 -new -newkey sphincssha256128frobust -keyout spx_CA.key -out spx_CA.crt -nodes -subj "/CN=sphincs+ CA" -days 365 -config apps/openssl.cnf
cat spx_CA.key spx_CA.crt >> spx_CA.pem
cp ./spx_CA.pem ../pqc-app/bin/crt/
```
---
###  Build
```
cd pqc-app
export LD_LIBRARY_PATH=$PWD/lib
cd app
qmake
make -j
```

### Client Run
```
cd pqc-app/
export LD_LIBRARY_PATH=$PWD/lib
cd bin/
./chat
```

### Server Run
```
cd pqc-app/
export LD_LIBRARY_PATH=$PWD/lib
cd bin/
./tlsserver-test 12345 crt/spx_CA.pem
```

# Open a file that chat.pro with Qt creator (Open Project)
File Location - pqc-app/app/chat.pro   
Qt creator's Projects tab - run tab - "Run as a root user" check   
Now you can run the program

===
기초 틀 - https://github.com/cryptogus/network-library-gilgil   
https://github.com/cryptogus/KeySoon-TCP-TLS
# Qt creator 사용
TCP 로 상속 받고 PQC class를 만들어서 쏘면 PQC 통신이라 하는데

# dummy interface 추가
다음과 같은 명령어로 dummy interface를 추가한다.  

```sudo ip link add dum0 type dummy```  
```sudo ifconfig dum0 up```  
# 추가된 interface는 추후 다음과 같은 명령어로 삭제할 수 있다.    
```sudo ip link del dum0```
  
# IP할당  
```sudo dhclinet -i dum0```


사용법
=============
1. app 폴더에서  
2. test 할 곳으로 들어간다
3. *.pro (qmake) QT로 open project해서 연다
4. 왼쪽 메뉴바의 Edit과 Debugs 아래 Projects를 클릭
5. Build와 Run 중 Run 선택
6. Command line arguments 에 argv[1] 부터 들어가야할 인자 넣어주기

원하는 코드 동작
-------------
클라이언트의 dum0 더미 인터페이스에서 dhcp discover 패킷이 발생되면
dhcp discover 패킷을 tcp통신으로 서버에게 보냅니다.
이를 받은 서버는 dhcp discover를 서버가 위치한 사설 대역에 브로드캐스트를 하게 됩니다.

최종적으로 VPN 통신 및 PQC VPN
