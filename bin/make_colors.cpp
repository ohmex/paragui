#include <string>
#include <fstream>
#include <iostream>
#include <vector>

std::string rgbfile = "rgb.txt";
std::string outfile = "pgcolors";

typedef struct {
    int r,g,b;
    std::string name;
} color_t;

std::vector<color_t> colors;

void output(std::ofstream& h, std::ofstream& c, int r, int g, int b, const std::string& n) {
    std::string constfmt = "\tconst PG_Color %s = 0x%02x%02x%02x;\n";
    std::string codefmt = "\tcolors[\"%s\"] = PG_Colormap::%s;\n";
    char buffer[256];
    
    snprintf(buffer, sizeof(buffer), constfmt.c_str(), n.c_str(), r, g, b);
    h << buffer;

    snprintf(buffer, sizeof(buffer), codefmt.c_str(), n.c_str(), n.c_str());
    c << buffer;
}

const char* f_top =
"/*\n"
"    ParaGUI - crossplatform widgetset\n"
"    Copyright (C) 2000,2001,2002,2003,2004  Alexander Pipelka\n"
"\n"
"    This library is free software; you can redistribute it and/or\n"
"    modify it under the terms of the GNU Library General Public\n"
"    License as published by the Free Software Foundation; either\n"
"    version 2 of the License, or (at your option) any later version.\n"
"\n"
"    This library is distributed in the hope that it will be useful,\n"
"    but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU\n"
"    Library General Public License for more details.\n"
"\n"
"    You should have received a copy of the GNU Library General Public\n"
"    License along with this library; if not, write to the Free\n"
"    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA\n"
"\n"
"    Alexander Pipelka\n"
"    pipelka@teleweb.at\n"
"\n"
"    Last Update:      $Author: braindead $\n"
"    Update Date:      $Date: 2006/12/04 12:20:50 $\n"
"    Source File:      $Source: /sources/paragui/paragui/bin/Attic/make_colors.cpp,v $\n"
"    CVS/RCS Revision: $Revision: 1.1.2.3 $\n"
"    Status:           $State: Exp $\n\n"
"    AUTOGENERATED PLEASE DO NOT EDIT!\n"
"*/\n"
"#include \"paragui.h\"\n"
"#ifdef ENABLE_PGCOLORS\n"
"\n"
"/** @file pgcolors.h\n"
"	Header file of the PG_Colors class.\n"
"	This header file also creates a bunch of useful color constants. To enable the\n"
"	creation of the color constants define \"USE_COLOR_CONSTANTS\" before including\n"
"	this header file.\n"
"	There are 891 predefined color constants, though many of them are duplicates\n"
"	differing in spelling and capitalization. @ref predefcolorlist \"List of all the\n"
"	predefined colors.\""
"*/\n\n";

const char* f_bottom =
"#endif // ENABLE_PGCOLORS\n";

const char* class_def =
"/**\n"
"	@author Marek Habersack\n"
"	@short tool-class for descriptive colorvalues\n"
"*/\n"
"\n"
"\n"
"class PG_Colors {\n"
" typedef STL_MAP<const char*, PG_Color> colormap;\n"
" typedef STL_MAP<const char*, PG_Color>::iterator cit;\n\n"
" public:\n"
"   PG_Colors() { if (!PG_Colors::initialized) {PG_Colors::InitColors(); PG_Colors::initialized = true;}}\n"
"   static bool FindColorByName(const char *name, PG_Color &c) {\n"
"       cit col = PG_Colors::colors.find(name);\n"
"       if (col != PG_Colors::colors.end()) {\n"
"           c = colors[name];\n"
"           return true;\n"
"       }\n"
"       return false;\n"
"   }\n\n"
"   static const PG_Color FindColorByName(const char *name) {\n"
"       PG_Color c;\n"
"	if(FindColorByName(name, c)) {\n"
"		return c;\n"
"	}"
"       return colors[\"black\"];\n"
"   }\n\n"
"   static void InitColors();\n\n"
"   const PG_Color operator[](const char *name) {\n"
"        return FindColorByName(name);\n"
"   }\n"
" protected:\n"
"   static colormap colors;\n"
"   static bool     initialized;\n"
"};\n"
"\n";

void generate_code() {

    std::ofstream h((outfile+".h").c_str());
    std::ofstream c((outfile+".cpp").c_str());

    h << f_top;
    h << "/** \\page predefcolorlist A list of all the predefined colors.\n";

    h << "@verbatim\n";
    for(int i=0; i<colors.size(); i++) {
	h << colors[i].name << "\n";
    }
    
    h << "@endverbatim\n";
    h << "*/\n\n";

    h << "#ifndef PG_COLORS_H\n";
    h << "#define PG_COLORS_H\n\n";
    h << "#include \"paragui.h\"\n";
    h << "#include \"pgcolor.h\"\n";
    h << "#include MAP_INC\n\n";
    h << "#ifdef USE_COLOR_CONSTANTS\n";
    h << "\n";
    h << "namespace PG_Colormap {\n";
    
    c << f_top;
    c << "#define USE_COLOR_CONSTANTS\n";
    c << "#include \"" << outfile << ".h\"\n\n";
    c << "PG_Colors::colormap PG_Colors::colors;\n";
    c << "bool PG_Colors::initialized = false;\n\n";
    c << "void PG_Colors::InitColors() {\n";

    for(int i=0; i<colors.size(); i++) {
        output(h, c, colors[i].r, colors[i].g, colors[i].b, colors[i].name);
    }

    h << "} // namespace PG_Colormap\n";
    h << "#endif // !USE_COLOR_CONSTANTS\n\n";
    h << class_def;
    h << "#endif // !PG_COLORS_H\n";
    h << f_bottom;

    c << "}\n";
    c << f_bottom;
}

void process_line(std::string& line) {
    int r,g,b;
    char name1[50];
    char name2[50];
    char name3[50];

    if(line[0] == '!' || line[0] == '#' || line[0] == ' ' || line.size() == 0) {
	return;
    }

    /*for(int i=0; i<line.size(); i++) {
	line[i] = tolower(line[i]);
    }*/

    name1[0] = 0;
    name2[0] = 0;
    name3[0] = 0;
    sscanf(line.c_str(), "%i %i %i %s %s %s", &r, &g, &b, name1, name2, name3);
    
    color_t c;
    c.r = r;
    c.g = g;
    c.b = b;
    c.name = name1;
    if(name2[0] != 0) {
	c.name += "_";
	c.name += name2;
    }
    if(name3[0] != 0) {
	c.name += "_";
	c.name += name3;
    }
    colors.push_back(c);
}

int main(int argc, char* argv[])
{
    if (argc > 1)
        rgbfile = argv[1];

    std::ifstream f(rgbfile.c_str());	
    
    if(!f.is_open()) {
        std::cerr << "Cannot open file '" << rgbfile << "' for reading\n";
        return 1;
    }

    std::vector<std::string> lines;
    std::string line;

    while(std::getline(f, line)) {
        process_line(line);
    }

    generate_code();
    return 0;
}
