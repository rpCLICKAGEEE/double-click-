#include <iostream>
#include <Windows.h>
#include <string>
#include <random>
#include <chrono>

bool CheckCredentials(const std::string& username, const std::string& password) {
    return ((username == "rpCLICKAGEE" && password == "rp") ||
        (username == "rpCLICKAGEE2" && password == "rp2") ||
        (username == "rpCLICKAGEE3" && password == "rp3"));
}

void StartDoubleClick(bool& doubleClickEnabled, int& cps) {
    doubleClickEnabled = true;
    std::cout << "Double clic active avec " << cps << " CPS." << std::endl;
}

int main() {
    std::string username, password;
    bool doubleClickEnabled = false;
    int cps = 20; // Défaut : 20 clics par seconde
    int delay = 1000 / cps;
    
    std::cout << "Entrer votre nom d'utilisateur : ";
    std::cin >> username;
    std::cout << "Entrer votre mot de passe : ";
    std::cin >> password;

    if (CheckCredentials(username, password)) {
        std::cout << "Authentification reussie." << std::endl;
        StartDoubleClick(doubleClickEnabled, cps);
    }
    else {
        std::cout << "Nom d'utilisateur ou mot de passe incorrect." << std::endl;
        return 0; // 
    }

    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(-20, 20); // Distribution uniforme de -20 à 20 millisecondes
    while (true) {
        if (doubleClickEnabled && (GetAsyncKeyState(VK_LBUTTON) & 0x8000)) {
            // Envoyer deux clics successifs
            INPUT input[2] = { 0 };
            input[0].type = INPUT_MOUSE;
            input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
            input[1].type = INPUT_MOUSE;
            input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

            SendInput(1, &input[0], sizeof(INPUT));
            Sleep(delay + distribution(generator));

            // Envoyer le deuxième clic
            SendInput(1, &input[1], sizeof(INPUT));
        }
        Sleep(10);
    }

    return 0;
}
