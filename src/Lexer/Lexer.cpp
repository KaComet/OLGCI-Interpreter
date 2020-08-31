#include "Lexer.h"
#include "ILexerComponent.h"
#include "DefineLexerComponent.h"
#include "PrintLexerComponent.h"

std::pair<std::string, Lexicon> lexicon_data[] = {
        std::make_pair("Define", Lexicon::Define),
        std::make_pair("Print", Lexicon::Print),
};

const std::map<std::string, Lexicon> lexicon(lexicon_data, lexicon_data + sizeof lexicon_data / sizeof lexicon_data[0]);


Lexer::Lexer() {
    defineComponent = std::make_shared<DefineLexerComponent>();
    printComponent = std::make_shared<PrintLexerComponent>();
}

template<typename C>
std::weak_ptr<C> getLexerComponent() {
    throw std::runtime_error("getLexerComponent for component not defined.");
};

void Lexer::run(std::ifstream &file) {
    while (!file.eof()) {
        std::string tmp;
        file >> tmp;
        Lexicon thisLex;

        if (tmp.empty())
            continue;

        try {
            thisLex = lexicon.at(tmp);
        } catch (std::out_of_range &e) {
            std::cout << "Symbol \"" << tmp << "\" not recognized. Exiting...";
            std::exit(1);
        }

        switch (thisLex) {
            case Lexicon::Define:
                defineComponent->run(file, environment);
                break;


            case Lexicon::Print:
                printComponent->run(file, environment);
                break;
        }


    }
}