#include <pybind11/embed.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string>

#include "languages.cpp"

namespace py = pybind11;

void translate(
	std::string from,
	std::string to,
	std::string input,
	std::string output
) {
    py::scoped_interpreter guard{};

	py::module_ translate = py::module_::import("argostranslate.translate");
	py::module_ package = py::module_::import("argostranslate.package");

	py::list installed_langs = translate.attr("get_installed_languages")();
	std::vector<std::string> available_languages; 

	for(auto i = 0; i < py::len(installed_langs); i++) {
		auto lang = installed_langs[i].attr("code");

		available_languages.push_back(std::string(py::str(lang)));
	}

    if(
		std::find(
			available_languages.begin(), 
			available_languages.end(), 
			from
		) == available_languages.end()
	) {
        throw std::invalid_argument("Not a valid input language.");
    }

	if(
		std::find(
			available_languages.begin(), 
			available_languages.end(), 
			to
		) == available_languages.end()
	) {
        throw std::invalid_argument("Not a valid output language.");
    }

	output = "hello world";
}

int main() {
	std::string result;
	translate("en", "es", "Hola", result);

	printf("Adress of return value s = %p is the same\n\n", &result); 
}