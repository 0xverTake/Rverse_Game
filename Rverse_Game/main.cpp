#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <conio.h>
#include <chrono>
#include <thread>
#include <TlHelp32.h>

// XOR encryption key (hidden in plain sight)
const char KEY[] = "R3V3RS3";

class AntiCheat {
private:
    bool isDebuggerDetected() {
        return IsDebuggerPresent();
    }

    bool isTimingAttackDetected() {
        static auto lastCallTime = std::chrono::steady_clock::now();
        auto currentTime = std::chrono::steady_clock::now();
        auto timeDiff = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastCallTime).count();
        lastCallTime = currentTime;
        return timeDiff < 100; // Detecting too rapid inputs
    }

    bool isMemoryScannerDetected() {
        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (snapshot == INVALID_HANDLE_VALUE) return false;

        PROCESSENTRY32W processEntry;
        processEntry.dwSize = sizeof(processEntry);

        if (Process32FirstW(snapshot, &processEntry)) {
            do {
                std::wstring processName = processEntry.szExeFile;
                // Check for common memory scanning tools
                if (processName.find(L"cheatengine") != std::wstring::npos ||
                    processName.find(L"x64dbg") != std::wstring::npos ||
                    processName.find(L"ollydbg") != std::wstring::npos) {
                    CloseHandle(snapshot);
                    return true;
                }
            } while (Process32NextW(snapshot, &processEntry));
        }

        CloseHandle(snapshot);
        return false;
    }

public:
    enum class DetectionType {
        DEBUGGER,
        TIMING,
        MEMORY_SCANNER,
        NONE
    };

    DetectionType checkForCheats() {
        if (isDebuggerDetected()) return DetectionType::DEBUGGER;
        if (isTimingAttackDetected()) return DetectionType::TIMING;
        if (isMemoryScannerDetected()) return DetectionType::MEMORY_SCANNER;
        return DetectionType::NONE;
    }
};

class ConsoleHelper {
public:
    static void SetConsoleColor(int color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    static void ClearScreen() {
        system("cls");
    }
};

class LanguageManager {
public:
    enum class Language { EN, FR };

private:
    Language currentLanguage;
    struct Translations {
        std::string welcome;
        std::string enterPassword;
        std::string incorrect;
        std::string success;
        std::string gameOver;
        std::string hint;
        std::string claudeHelp;
        std::string debuggerDetected;
        std::string timingDetected;
        std::string memoryToolDetected;
        std::string antiCheatHelp;
        std::vector<std::string> hints;
    };

    Translations en = {
        "Welcome to the Reverse Engineering Challenge!\nLevel 1: Password Cracking\n\n"
        "Your goal is to find the correct password by analyzing the source code.\n"
        "Type 'hint' for a hint, 'claude' for help, 'anticheat' for anti-cheat info, or 'quit' to exit.\n",
        "Enter password: ",
        "Incorrect password. %d attempts remaining.",
        "Congratulations! You've successfully reversed the password!",
        "Maximum attempts reached. Game Over.",
        "HINT",
        "CLAUDE AI HELP",
        "\n[ANTI-CHEAT] Debugger detected! Nice try...\nTip: Try to bypass the IsDebuggerPresent check\n",
        "\n[ANTI-CHEAT] Timing attack detected! Slow down...\nTip: The timing check measures input intervals\n",
        "\n[ANTI-CHEAT] Memory scanning tool detected!\nTip: Process scanning can be bypassed by process name obfuscation\n",
        "\n[ANTI-CHEAT INFO] Current protections:\n"
        "1. Debugger Detection\n   - Uses IsDebuggerPresent()\n   - Can be bypassed by patching the PEB\n\n"
        "2. Timing Attack Detection\n   - Measures input intervals\n   - Can be bypassed by adding delays\n\n"
        "3. Memory Scanner Detection\n   - Scans for known tool names\n   - Can be bypassed by renaming tools\n\n"
        "Security fixes would include:\n"
        "- Advanced integrity checks\n"
        "- Code obfuscation\n"
        "- Anti-debugging techniques\n"
        "- Memory checksum verification\n",
        {
            "The password is encrypted using XOR operation",
            "XOR has a special property: A ^ B ^ B = A",
            "Look at the encryption key and how it's used",
            "Try to understand the pattern in the encrypted bytes",
            "The password length matches the encrypted bytes length"
        }
    };

    Translations fr = {
        "Bienvenue dans le Défi de Rétro-Ingénierie !\nNiveau 1 : Craquage de Mot de Passe\n\n"
        "Votre objectif est de trouver le mot de passe correct en analysant le code source.\n"
        "Tapez 'hint' pour un indice, 'claude' pour de l'aide, 'anticheat' pour info anti-triche, ou 'quit' pour quitter.\n",
        "Entrez le mot de passe : ",
        "Mot de passe incorrect. %d tentatives restantes.",
        "Félicitations ! Vous avez réussi à décrypter le mot de passe !",
        "Nombre maximum de tentatives atteint. Partie terminée.",
        "INDICE",
        "AIDE CLAUDE IA",
        "\n[ANTI-TRICHE] Débogueur détecté ! Bien essayé...\nAstuce : Essayez de contourner la vérification IsDebuggerPresent\n",
        "\n[ANTI-TRICHE] Attaque temporelle détectée ! Ralentissez...\nAstuce : La vérification temporelle mesure les intervalles de saisie\n",
        "\n[ANTI-TRICHE] Outil de scan mémoire détecté !\nAstuce : La détection des processus peut être contournée en masquant le nom du processus\n",
        "\n[INFO ANTI-TRICHE] Protections actuelles :\n"
        "1. Détection de Débogueur\n   - Utilise IsDebuggerPresent()\n   - Peut être contourné en modifiant le PEB\n\n"
        "2. Détection d'Attaque Temporelle\n   - Mesure les intervalles de saisie\n   - Peut être contourné en ajoutant des délais\n\n"
        "3. Détection de Scanner Mémoire\n   - Recherche des noms d'outils connus\n   - Peut être contourné en renommant les outils\n\n"
        "Les correctifs de sécurité incluraient :\n"
        "- Vérifications d'intégrité avancées\n"
        "- Obscurcissement du code\n"
        "- Techniques anti-débogage\n"
        "- Vérification des checksums mémoire\n",
        {
            "Le mot de passe est crypté en utilisant l'opération XOR",
            "XOR a une propriété spéciale : A ^ B ^ B = A",
            "Regardez la clé de cryptage et comment elle est utilisée",
            "Essayez de comprendre le motif dans les octets cryptés",
            "La longueur du mot de passe correspond à la longueur des octets cryptés"
        }
    };

public:
    LanguageManager() : currentLanguage(Language::EN) {}

    void SetLanguage(Language lang) {
        currentLanguage = lang;
        ConsoleHelper::ClearScreen();
        PrintWelcome();
    }

    void PrintWelcome() const {
        ConsoleHelper::SetConsoleColor(10); // Green
        std::cout << GetCurrentTranslation().welcome << std::endl;
    }

    void PrintPasswordPrompt() const {
        ConsoleHelper::SetConsoleColor(10); // Green
        std::cout << GetCurrentTranslation().enterPassword;
    }

    void PrintIncorrect(int attemptsLeft) const {
        ConsoleHelper::SetConsoleColor(12); // Red
        printf((GetCurrentTranslation().incorrect + "\n").c_str(), attemptsLeft);
    }

    void PrintSuccess() const {
        ConsoleHelper::SetConsoleColor(10); // Green
        std::cout << GetCurrentTranslation().success << std::endl;
    }

    void PrintGameOver() const {
        ConsoleHelper::SetConsoleColor(12); // Red
        std::cout << GetCurrentTranslation().gameOver << std::endl;
    }

    void PrintHint() const {
        ConsoleHelper::SetConsoleColor(14); // Yellow
        std::cout << "\n[" << GetCurrentTranslation().hint << "] ";
        const auto& hints = GetCurrentTranslation().hints;
        std::cout << hints[rand() % hints.size()] << std::endl;
    }

    void PrintClaudeHelp() const {
        ConsoleHelper::SetConsoleColor(11); // Light Cyan
        std::cout << "\n[" << GetCurrentTranslation().claudeHelp << "]\n";
        if (currentLanguage == Language::EN) {
            std::cout << "1. XOR encryption is reversible using the same key\n";
            std::cout << "2. The encryption key is visible in the source code\n";
            std::cout << "3. You can analyze the encryption function\n";
            std::cout << "4. Try understanding how the key is used\n";
            std::cout << "5. The password length is 6 characters\n";
        }
        else {
            std::cout << "1. Le cryptage XOR est réversible avec la même clé\n";
            std::cout << "2. La clé de cryptage est visible dans le code source\n";
            std::cout << "3. Vous pouvez analyser la fonction de cryptage\n";
            std::cout << "4. Essayez de comprendre comment la clé est utilisée\n";
            std::cout << "5. Le mot de passe fait 6 caractères\n";
        }
    }

    void PrintAntiCheatDetection(AntiCheat::DetectionType type) const {
        ConsoleHelper::SetConsoleColor(12); // Red
        switch (type) {
            case AntiCheat::DetectionType::DEBUGGER:
                std::cout << GetCurrentTranslation().debuggerDetected;
                break;
            case AntiCheat::DetectionType::TIMING:
                std::cout << GetCurrentTranslation().timingDetected;
                break;
            case AntiCheat::DetectionType::MEMORY_SCANNER:
                std::cout << GetCurrentTranslation().memoryToolDetected;
                break;
        }
    }

    void PrintAntiCheatHelp() const {
        ConsoleHelper::SetConsoleColor(11); // Light Cyan
        std::cout << GetCurrentTranslation().antiCheatHelp;
    }

private:
    const Translations& GetCurrentTranslation() const {
        return currentLanguage == Language::EN ? en : fr;
    }
};

class SecuritySystem {
private:
    std::string encryptDecrypt(const std::string& input) {
        std::string output = input;
        for (size_t i = 0; i < input.length(); i++) {
            output[i] = input[i] ^ KEY[i % sizeof(KEY)];
        }
        return output;
    }

    const std::string ENCRYPTED_PASSWORD = { 0x35, 0x1E, 0x17, 0x1A, 0x12, 0x1F }; // "LEVEL1"
    int attempts = 0;
    const int MAX_ATTEMPTS = 5;
    LanguageManager lang;
    AntiCheat antiCheat;

public:
    void run() {
        lang.PrintWelcome();

        while (attempts < MAX_ATTEMPTS) {
            // Check for cheating attempts
            auto detectionType = antiCheat.checkForCheats();
            if (detectionType != AntiCheat::DetectionType::NONE) {
                lang.PrintAntiCheatDetection(detectionType);
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }

            lang.PrintPasswordPrompt();
            
            std::string input;
            std::getline(std::cin, input);

            // Convert to uppercase for comparison
            for (char& c : input) c = toupper(c);

            if (input == "QUIT") {
                return;
            }
            else if (input == "HINT") {
                lang.PrintHint();
                continue;
            }
            else if (input == "CLAUDE") {
                lang.PrintClaudeHelp();
                continue;
            }
            else if (input == "ANTICHEAT") {
                lang.PrintAntiCheatHelp();
                continue;
            }
            else if (input == "FR") {
                lang.SetLanguage(LanguageManager::Language::FR);
                continue;
            }
            else if (input == "EN") {
                lang.SetLanguage(LanguageManager::Language::EN);
                continue;
            }

            if (encryptDecrypt(input) == ENCRYPTED_PASSWORD) {
                lang.PrintSuccess();
                return;
            }

            attempts++;
            if (attempts < MAX_ATTEMPTS) {
                lang.PrintIncorrect(MAX_ATTEMPTS - attempts);
            }
            else {
                lang.PrintGameOver();
            }
        }
    }
};

// Debug function (intentionally left in the code as a hint)
void _dbg_generate_password(const std::string& pass) {
    std::string output = pass;
    for (size_t i = 0; i < pass.length(); i++) {
        output[i] = pass[i] ^ KEY[i % sizeof(KEY)];
    }
    std::cout << "Encrypted bytes: ";
    for (char c : output) {
        printf("0x%02X, ", static_cast<unsigned char>(c));
    }
    std::cout << "\n";
}

int main() {
    // Set console title
    SetConsoleTitle(L"Reverse Engineering Challenge");
    
    // Enable console colors
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD consoleMode;
    GetConsoleMode(hConsole, &consoleMode);
    SetConsoleMode(hConsole, consoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    // Seed random for hints
    srand(static_cast<unsigned>(time(nullptr)));

    // Run the security system
    SecuritySystem security;
    security.run();

    // Debug line (commented out but left as a hint)
    // _dbg_generate_password("LEVEL1");

    ConsoleHelper::SetConsoleColor(7); // Reset color
    std::cout << "\nPress any key to exit...";
    _getch();
    return 0;
}