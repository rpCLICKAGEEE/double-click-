#include <iostream>
#include <Windows.h>
#include <string>
#include <random>
#include <chrono>

void StartDoubleClick(bool& doubleClickEnabled, int& cps) {
    doubleClickEnabled = true;
    std::cout << "Double clic active avec " << cps << " CPS." << std::endl;
}

void SetCPS(int& cps) {
    std::string input;
    while (true) {
        std::cout << "Veuillez entrer le nombre de clics par seconde (CPS) : ";
        std::cin >> input;

        try {
            cps = std::stoi(input);
            if (cps > 0) {
                break;
            }
            else {
                std::cout << "Veuillez entrer un nombre de CPS valide (supérieur à 0)." << std::endl;
            }
        }
        catch (std::invalid_argument&) {
            std::cout << "Veuillez entrer un nombre valide." << std::endl;
        }
    }
}

int main() {
    std::string username, password;
    bool doubleClickEnabled = false; // Indicateur pour savoir si le double clic est activé
    int cps = 20; // Défaut : 20 clics par seconde
    int delay = 1000 / cps; // Défaut : délai entre les clics en millisecondes pour le nombre de CPS spécifié

    SetConsoleTitleA("");

    std::cout << "Entrer votre nom d'utilisateur : ";
    std::cin >> username;
    std::cout << "Entrer votre mot de passe : ";
    std::cin >> password;

    if (username == "rpCLICKAGEE" && password == "rp") {
        StartDoubleClick(doubleClickEnabled, cps);
    }
    else {
        std::cout << "Nom d'utilisateur ou mot de passe incorrect." << std::endl;
        return 0;
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
            SendInput(1, &input[1], sizeof(INPUT));
        }
        Sleep(10);
    }
    return 0;
}
