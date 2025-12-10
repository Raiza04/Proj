#include "inc/main.hpp"
#include "inc/bubblesort.hpp"
#include "inc/quicksort.hpp"
#include "inc/mergesort.hpp"
#include "inc/insertion.hpp"

// Definition der globalen Variablen
int BAR_NUM = 300;
float BAR_WIDTH = static_cast<float>(WINDOW_WIDTH) / BAR_NUM;
int SLEEP_MS = 10;

Config parseArguments(int argc, char* argv[]) {
    Config config;
    
    auto printUsage = [&]() {
        std::cerr << "Verwendung: " << argv[0] << " [OPTIONEN]\n\n"
                  << "Optionen (reihenfolge-unabhängig):\n"
                  << "  -a <algo>   Algorithmus: quick, merge, insert, bubble (Standard: bubble)\n"
                  << "  -n <num>    Anzahl der Balken (Standard: 300, Max: " << WINDOW_WIDTH << ")\n"
                  << "  -s <ms>     Sleep-Zeit in Millisekunden (Standard: 10)\n\n"
                  << "Beispiele:\n"
                  << "  " << argv[0] << " -a quick -n 150 -s 5\n"
                  << "  " << argv[0] << " -s 10 -n 100 -a bubble\n";
    };

    for (int i = 1; i < argc; i += 2) {
        if (i + 1 >= argc) {
            std::cerr << "Fehler: Wert fehlt für '" << argv[i] << "'\n";
            printUsage();
            exit(1);
        }

        std::string flag = argv[i];
        std::string value = argv[i + 1];

        if (flag == "-a") {
            config.algorithm = value;
        } else if (flag == "-n") {
            try {
                config.bar_num = std::stoi(value);
                if (config.bar_num <= 0 || config.bar_num > WINDOW_WIDTH) {
                    throw std::out_of_range("Ungültiger Bereich");
                }
            } catch (...) {
                std::cerr << "Fehler: Ungültige Balkenanzahl '" << value << "'\n";
                exit(1);
            }
        } else if (flag == "-s") {
            try {
                config.sleep_ms = std::stoi(value);
                if (config.sleep_ms < 0) throw std::out_of_range("Negativer Wert");
            } catch (...) {
                std::cerr << "Fehler: Ungültige Sleep-Zeit '" << value << "'\n";
                exit(1);
            }
        } else {
            std::cerr << "Fehler: Unbekannter Parameter '" << flag << "'\n";
            printUsage();
            exit(1);
        }
    }

    if (config.algorithm != "quick" && config.algorithm != "merge" && 
        config.algorithm != "insert" && config.algorithm != "bubble") {
        std::cerr << "Fehler: Unbekannter Algorithmus '" << config.algorithm << "'\n";
        printUsage();
        exit(1);
    }

    return config;
}

int main(int argc, char* argv[]) {
    Config config = parseArguments(argc, argv);
    
    // Globale Variablen setzen
    BAR_NUM = config.bar_num;
    BAR_WIDTH = static_cast<float>(WINDOW_WIDTH) / BAR_NUM;
    SLEEP_MS = config.sleep_ms;

    std::cout << "Starte " << config.algorithm << "sort mit " 
              << BAR_NUM << " Balken und " << SLEEP_MS << "ms delay\n";

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    std::vector<int> values(BAR_NUM);
    for (int& v : values) {
        v = std::rand() % WINDOW_HEIGHT;
    }

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),"Sort Visualizer - " + config.algorithm + "sort");

    if (config.algorithm == "quick") {
        quicksort(window, values, 0, values.size() - 1);
    } else if (config.algorithm == "merge") {
        mergesort(window, values, 0, values.size() - 1);
    } else if (config.algorithm == "insert") {
        insertion(window, values);
    } else if (config.algorithm == "bubble") {
        BubbleSortState sort;
        while (window.isOpen() && !sorted(values)) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
            }
            sort.step(values, window);
        }
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }
        drawArr(window, -1, values);
    }

    return 0;
}