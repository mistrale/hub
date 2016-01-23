#include "library.h"
#include "ui_library.h"

#include <QDir>
#include <QFileInfoList>

#include <iostream>

#include <iostream>
#include <iomanip>
#include <stdio.h>

#include <fileref.h>
#include <tag.h>
#include <tpropertymap.h>


GUI::Library::Library(QWidget *parent) :
    AWidget(parent),
    ui(new Ui::Library)
{
    ui->setupUi(this);
}

GUI::Library::~Library()
{
    delete ui;
}

void        GUI::Library::initialize() {
    TagLib::FileRef f(argv[i]);

    if(!f.isNull() && f.tag()) {

      TagLib::Tag *tag = f.tag();

      cout << "-- TAG (basic) --" << endl;
      cout << "title   - \"" << tag->title()   << "\"" << endl;
      cout << "artist  - \"" << tag->artist()  << "\"" << endl;
      cout << "album   - \"" << tag->album()   << "\"" << endl;
      cout << "year    - \"" << tag->year()    << "\"" << endl;
      cout << "comment - \"" << tag->comment() << "\"" << endl;
      cout << "track   - \"" << tag->track()   << "\"" << endl;
      cout << "genre   - \"" << tag->genre()   << "\"" << endl;

      TagLib::PropertyMap tags = f.file()->properties();

      unsigned int longest = 0;
      for(TagLib::PropertyMap::ConstIterator i = tags.begin(); i != tags.end(); ++i) {
        if (i->first.size() > longest) {
          longest = i->first.size();
        }
      }

      cout << "-- TAG (properties) --" << endl;
      for(TagLib::PropertyMap::ConstIterator i = tags.begin(); i != tags.end(); ++i) {
        for(TagLib::StringList::ConstIterator j = i->second.begin(); j != i->second.end(); ++j) {
          cout << left << std::setw(longest) << i->first << " - " << '"' << *j << '"' << endl;
        }
      }

    }

//    QDir dir("C:/document");
//    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
//    dir.setSorting(QDir::Size | QDir::Reversed);

//    QFileInfoList list = dir.entryInfoList();
//    std::cout << "     Bytes Filename" << std::endl;
//    for (int i = 0; i < list.size(); ++i) {
//        QFileInfo fileInfo = list.at(i);
//        std::cout << qPrintable(QString("%1 %2 %3").arg(fileInfo.size(), 10)
//                                                .arg(fileInfo.fileName()).arg(fileInfo.owner()));
//        std::cout << std::endl;
//    }
}
