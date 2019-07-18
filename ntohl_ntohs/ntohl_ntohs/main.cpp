
// Environment: Visual Studio

#include <stdint.h>
#include <stdio.h>
#include <winsock.h>

// https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-ntohs
// microsoft ntohs function google search
// winsock.h 링크걸기위해서는 Win2_32.lib 라이브러리 파일을 추가해줘야한다.
// link option = 프로젝트 - 속성 - 링커 - 입력 - 추가 종속성 - 제일 뒤에 ;Win2_32.lib

uint16_t my_ntohs(uint16_t n) {
	//return ((n << 8) & 0xFF00) | ((n >> 8) & 0x00FF);
	return n << 8 | n >> 8;

	// 34 12
	// 12 00 ( << 8 )
	// 00 34 ( >> 8 ) |
	// ------------------
	// 12 34
}

uint32_t my_ntohl(uint32_t n) {
	return ((n << 24) & 0xFF000000) |
		((n << 8) & 0x00FF0000) |
		((n >> 8) & 0x0000FF00) |
		((n >> 24) & 0x000000FF);

	// 78 56 34 12
	// 00 00 00 78	( >> 24 )
	// 00 00 56		( << 8 )
	// 00 34		( >> 8 )
	// 12			( << 24 ) |
	// -------------------------
	// 12 34 56 78
}

int main() {
	uint8_t packet[] = { 0x12, 0x34, 0x56, 0x78 };
	uint32_t* p = reinterpret_cast<uint32_t*>(packet); // type casting
	uint32_t ip = *p;
	ip = my_ntohl(ip);
	printf("%x\n", ip);

	// ip를 출력했을 때, 80이 나와야하는데 20480라는 큰 숫자가 나온다. 20480은 16진수=0x5000이다.
	// 따라서
	// 12 34 56 78로 출력하려고 했을 때, 78 56 34 12로 출력되므로 ntohls를 해줘야한다.
}

