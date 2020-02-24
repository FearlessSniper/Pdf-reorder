/**
 * @file pdf-reorder.cpp
 * @author FearlessSniper (47030588+FearlessSniper@users.noreply.github.com)
 * @brief Reorders a PDF document to the correct order with the original order
 *        be odd pages, then even pages
 * @version 0.1
 * @date 2020-02-24
 */
#include <iostream>
#include <string>
#include <cmath>
#include "pdf-reorder.h"

using namespace std;
using namespace PoDoFo;

int main(){
    cout << "Please enter the PDF path: " << flush;
    string pdf_path;
    getline(cin, pdf_path);
    PdfMemDocument pdf_file(pdf_path.c_str()), new_pdf_file;
    new_pdf_file.Append(pdf_file);
    PdfObject *pages = new_pdf_file.GetCatalog()->GetIndirectKey(PdfName("Pages"));
    reorder_page_odds_evens(pages);
    pdf_path.erase(pdf_path.find(".pdf"), string(".pdf").length());
    pdf_path += "_reordered.pdf";
    new_pdf_file.Write(pdf_path.c_str());
    return 0;
}

/**
 * \brief Reorder the pages of the PDF Document with the original order be odd pages,
 * then even.
 * \param pages A pointer to the Pages object of the PdfMemDocument.
 */
void reorder_page_odds_evens(PdfObject *&pages){
    PdfArray page_kids = pages->GetIndirectKey(PdfName("Kids"))->GetArray(), new_page_kids;
    int n_pages = page_kids.size();
    new_page_kids.reserve(n_pages);
    PdfArray::iterator it = page_kids.begin();
    for (int i = 0, j = floor(n_pages / 2), k = 0; k < n_pages; i++, j++, k+=2){
        new_page_kids.push_back(*(it + i));
        if (it + j < page_kids.end()){
            new_page_kids.push_back(*(it + j));
        }
    }
    pages->GetDictionary().AddKey(PdfName("Kids"), new_page_kids);
}
