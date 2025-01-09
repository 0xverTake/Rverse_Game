# Reverse Engineering Challenge / Défi de Rétro-Ingénierie

A password cracking challenge game where users learn reverse engineering concepts.  
Un jeu de craquage de mot de passe où les utilisateurs apprennent les concepts de la rétro-ingénierie.

## 🇬🇧 English Instructions

### Prerequisites
- Visual Studio Community 2022 (free)
  - Download from: https://visualstudio.microsoft.com/vs/community/
  - During installation, select "Desktop development with C++"

### Project Setup
1. **Create New Project**
   - Open Visual Studio Community
   - Click "Create a new project"
   - Search for "Console App"
   - Select "Console App" for C++
   - Click Next
   - Project name: "ReverseEngineeringGame"
   - Choose your location
   - Click Create

2. **Configure Project**
   - Right-click on the project in Solution Explorer
   - Select Properties
   - Under Configuration Properties > General:
     * Set Windows SDK Version to latest available
     * Set Platform Toolset to Visual Studio 2022 (v143)
   - Under C/C++ > Language:
     * Set C++ Language Standard to ISO C++17 Standard (/std:c++17)
   - Click Apply and OK

3. **Add Source Code**
   - In Solution Explorer, open main.cpp
   - Delete all existing code
   - Copy and paste the provided main.cpp code
   - Save the file (Ctrl+S)

4. **Build and Run**
   - Press F5 or click the green play button
   - The game will run in a console window

### How to Play
- Try to find the correct password by analyzing the source code
- Available commands:
  - `hint`: Get a hint about the password
  - `claude`: Get help from Claude AI about reverse engineering
  - `anticheat`: Learn about anti-cheat protections and bypasses
  - `EN`: Switch to English
  - `FR`: Switch to French
  - `quit`: Exit the game
- You have 5 attempts to find the correct password
- Use the debug function and encryption key visible in the code to help you

### Anti-Cheat Features
The game includes several anti-cheat protections that you can try to bypass:

1. **Debugger Detection**
   - Uses Windows API IsDebuggerPresent()
   - Can be bypassed by:
     * Patching the PEB (Process Environment Block)
     * Modifying the debugger flag
     * Using advanced debugging techniques

2. **Timing Attack Detection**
   - Monitors input intervals
   - Can be bypassed by:
     * Adding delays between inputs
     * Modifying the timing check
     * Simulating natural input timing

3. **Memory Scanner Detection**
   - Detects common reverse engineering tools
   - Can be bypassed by:
     * Renaming tool executables
     * Using custom tools
     * Modifying process names

Learn about security vulnerabilities and how to fix them using the `anticheat` command.

## 🇫🇷 Instructions en Français

### Prérequis
- Visual Studio Community 2022 (gratuit)
  - Téléchargement : https://visualstudio.microsoft.com/vs/community/
  - Pendant l'installation, sélectionnez "Développement Desktop en C++"

### Configuration du Projet
1. **Créer un Nouveau Projet**
   - Ouvrez Visual Studio Community
   - Cliquez sur "Créer un nouveau projet"
   - Recherchez "Application console"
   - Sélectionnez "Application console" pour C++
   - Cliquez sur Suivant
   - Nom du projet : "ReverseEngineeringGame"
   - Choisissez l'emplacement
   - Cliquez sur Créer

2. **Configurer le Projet**
   - Clic droit sur le projet dans l'Explorateur de solutions
   - Sélectionnez Propriétés
   - Sous Propriétés de configuration > Général :
     * Définir la version du SDK Windows à la plus récente
     * Définir la Boîte à outils de la plateforme sur Visual Studio 2022 (v143)
   - Sous C/C++ > Langage :
     * Définir la Norme du langage C++ sur ISO C++17 Standard (/std:c++17)
   - Cliquez sur Appliquer et OK

3. **Ajouter le Code Source**
   - Dans l'Explorateur de solutions, ouvrez main.cpp
   - Supprimez tout le code existant
   - Copiez et collez le code main.cpp fourni
   - Sauvegardez le fichier (Ctrl+S)

4. **Compiler et Exécuter**
   - Appuyez sur F5 ou cliquez sur le bouton vert de lecture
   - Le jeu s'exécutera dans une fenêtre console

### Comment Jouer
- Essayez de trouver le mot de passe correct en analysant le code source
- Commandes disponibles :
  - `hint` : Obtenir un indice sur le mot de passe
  - `claude` : Obtenir l'aide de Claude IA sur la rétro-ingénierie
  - `anticheat` : En savoir plus sur les protections anti-triche et leurs contournements
  - `EN` : Passer en anglais
  - `FR` : Passer en français
  - `quit` : Quitter le jeu
- Vous avez 5 tentatives pour trouver le bon mot de passe
- Utilisez la fonction de débogage et la clé de cryptage visible dans le code pour vous aider

### Fonctionnalités Anti-Triche
Le jeu inclut plusieurs protections anti-triche que vous pouvez essayer de contourner :

1. **Détection de Débogueur**
   - Utilise l'API Windows IsDebuggerPresent()
   - Peut être contourné par :
     * Modification du PEB (Process Environment Block)
     * Modification du flag de débogage
     * Utilisation de techniques de débogage avancées

2. **Détection d'Attaque Temporelle**
   - Surveille les intervalles entre les saisies
   - Peut être contourné par :
     * Ajout de délais entre les saisies
     * Modification de la vérification temporelle
     * Simulation de timing naturel de saisie

3. **Détection de Scanner Mémoire**
   - Détecte les outils courants de rétro-ingénierie
   - Peut être contourné par :
     * Renommage des exécutables des outils
     * Utilisation d'outils personnalisés
     * Modification des noms de processus

Découvrez les vulnérabilités de sécurité et comment les corriger en utilisant la commande `anticheat`.

## 🛠️ Technical Details / Détails Techniques

### Features / Fonctionnalités
- XOR encryption/decryption
- Bilingual support (EN/FR)
- Color console output
- Hint system
- Claude AI helper
- Anti-cheat system with bypass challenges
- Debug functions for analysis

### Requirements / Prérequis Techniques
- Windows 10/11
- Visual Studio 2022
- C++17 support
- Windows SDK 10.0 or later