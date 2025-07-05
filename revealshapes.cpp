/***
 * 
 * Exportshapes is a program that extracts shape dictionary data 
 * from a djvu file into a database.
 *
 * Copyright © 2012 -- Piotr Sikora.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * 
 ***/

#include <iostream>
#include <exception>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <bits/getopt_core.h>
#include <bits/getopt_core.h>

#include "DjVuDocument.h"
#include "DjVuImage.h"
#include "/usr/include/libdjvu/ddjvuapi.h"
#include "DjVmDir.h"
#include "JB2Image.h"
#include "Arrays.h"
#include "GBitmap.h"
#include "UnicodeByteStream.h"

#include <cstdlib>
#include <unistd.h>
#include <filesystem>
#include <algorithm> 

using namespace std;

typedef std::pair<int, int> IntPair;

typedef struct {
	int right, top, left, bottom;
} BoundingBox;

#include <fstream>
std::ostream* out_stream = &std::cout;
std::ofstream out_file;
char *output_file = nullptr;
bool test_run = false, poliqarp = false;
char *filename;




int process_document(int page_from, int page_to, GP<DjVuDocument> doc) {
	const int pages = doc->get_pages_num();
	int page_start, page_limit;
	page_start = (page_from < 1) ? 0 : page_from - 1;
	if (page_to < 1 || page_to >= pages)
		page_limit = pages;
	else
		page_limit = page_to;
	if (page_limit <= page_start) {
		std::cout << "Can't process less than one page." << std::endl;
		return EXIT_FAILURE;
	}
    std::filesystem::path sorig = filename;
	std::string sorigString = sorig.string();
        sorigString.erase(std::remove_if(sorigString.begin(), sorigString.end(), [](char c) { return c == '\"'; }), sorigString.end());
	std::filesystem::path s = filename;
	std::cout << "sjbz or djbz,page number,blit number,blit shapeno,shape bits columns,rows,rowsize,blit bottom, left" << endl;


	for(int page_number = page_start; page_number < page_limit; page_number++) {

		GP<DjVuImage> djvu_page = doc->get_page(page_number);

		if (!djvu_page) {
			std::cout << "Failed to get DjVuImage for page" << page_number << std::endl;
		} else {

			GP<DjVuFile> djvu_file = djvu_page->get_djvu_file();
			GP<JB2Image> jimg = djvu_page->get_fgjb();
			if (!djvu_file) {
				std::cout << "Failed to get DjVUFile for page " << page_number << std::endl;
			} else if (!jimg) {
				std::cout << "Failed to get JB2Image for page " << page_number << std::endl;
			} else {//export shapes
				if (test_run)
					std::cout << "Processing page " << page_number << " containing " << jimg->get_shape_count() << " shapes, " << jimg->get_inherited_shape_count() << " of them inherited." << std::endl;
				GP<JB2Dict> inherited_dictionary = jimg->get_inherited_dict();
				// int inh_dict_id = -1;
				int inh_sh_count = jimg->get_inherited_shape_count();


				string page_name = (string) djvu_file->get_url().fname();
				int sh_count = jimg->get_shape_count();
				int blit_count = jimg->get_blit_count();

				if (test_run)
					std::cout << "Processing blits. " << std::endl;
				for (int i = 0; i < blit_count; i++) {
					JB2Blit *blit = jimg->get_blit(i);
					if (blit) {
						JB2Shape shape = jimg->get_shape(blit->shapeno);
						if (poliqarp ) {
							//<file-name> d-<blit number>-<blit shapeno>;file:<file-name>?djvuopts=&highlight=<left>,<blit bottom>,<shape bit columns>,<rows>&page=<page number + 1>; <file-name> d-<blit number>-<blit shapeno>;
							std::cout << s.replace_extension().filename();
							std::cout <<" d-" <<i <<"-" << blit->shapeno << ";";
std::cout << "file:" << sorigString << "?djvuopts=&highlight=" << blit->left << "," << blit->bottom << "," << shape.bits->columns() << "," << shape.bits->rows() << "&page=" << (page_number + 1) << ";";
							std::cout << s.filename() <<" d-" <<i <<"-" << blit->shapeno << std::endl;
						} else {
std::cout << ((blit->shapeno < inh_sh_count)?"s":"d") << "," << (page_number + 1) << "," << i << "," << blit->shapeno  << "," << shape.bits->columns() << ","  << shape.bits->rows() << ","  << shape.bits->rowsize() << "," << blit->bottom << ","  << blit->left << endl;
						}
					}
				}
			}
		}
	}
	return EXIT_SUCCESS;
}




void usage(char **argv) {
	std::cout << "Usage: " << argv[0] << "[-t <page #>] [-f <page #>] [-T] <filename>" << std::endl;
	std::cout << "Option -f: its argument specifies a page number from which the processing should start." << std::endl;
	std::cout << "Option -t: its argument specifies a limit to the number of pages processed by the program." << std::endl;
	std::cout << "Option -T: verbose" << std::endl;
}


int main(int argc, char **argv) {
	try {
		int c;
		int page_from = 1 , page_to = -1;
		bool test_run = false, links_only = false;

        // Extend option string to include 'o' and 'h'
        while ((c = getopt (argc, argv, "Tlpf:t:o:h")) != -1) {
		while ((c = getopt (argc, argv, "Tlpf:t:")) != -1) {
			switch (c) {
				case 'T':
        case 'o':
            output_file = optarg;
            break;
        case 'h':
            usage(argv[0]);
            exit(EXIT_SUCCESS);
					test_run = true;
					break;
				case 'f':
					page_from = atoi(optarg);
					break;
				case 't':
					page_to = atoi(optarg);
					break;
				case 'p':
					poliqarp = true;
					break;
				case 'l':
					links_only = true;
					break;
				case '?':
		    		cerr << "Unknown option: " << optopt << endl;
		         return 1;
		       default:
		         cerr << "Usage: " << argv[0] << " [-T] [-f page_from] [-t page_to] [-l] filename" << endl;
    // Open output file if specified
    if (output_file) {
        out_file.open(output_file);
        if (!out_file) {
            std::cerr << "Error: Cannot open output file: " << output_file << std::endl;
            exit(EXIT_FAILURE);
        }
        out_stream = &out_file;
    }
		         return 1;
		    }
		}

		if (optind == argc) {
			cerr << "Filename argument is missing." << endl;
			return 1;
		}

		filename = argv[optind];
		const GURL::Filename::UTF8 url(filename);


                GP<DjVuDocument> doc = DjVuDocument::create_wait(url);
 
                if (!doc) {
                       cerr << "cannot open file" << endl;
                       return -1;
                } else {
	               return process_document(page_from, page_to, doc);
		}

		// Additional argument checking if needed
		
		// Database operations removed
		
		// Remaining logic for processing the document
		std::cout << "Filename: " << filename << endl;
		std::cout << "Page From: " << page_from << endl;
		std::cout << "Page To: " << page_to << endl;
		std::cout << "Test Run: " << (test_run ? "true" : "false") << endl;
		std::cout << "Links Only: " << (links_only ? "true" : "false") << endl;

		// Process the document
		// Placeholder for document processing logic
		
		return EXIT_SUCCESS;
	}
	catch (exception& ex) {
		cerr << "An exception occurred: " << ex.what() << endl;
		return EXIT_FAILURE;
	}
}



