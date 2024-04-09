#include <iostream>
#include <Windows.h>

int main() {
    std::cout << "Cliquer une fois pour simuler un double-clic." << std::endl;

    while (true) {
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            INPUT input[2] = {0};
            input[0].type = INPUT_MOUSE;
            input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
            input[1].type = INPUT_MOUSE;
            input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
            SendInput(2, input, sizeof(INPUT));
        }
        Sleep(100);
    }

    return 0;
}
