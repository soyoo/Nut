#include "sampledatabase.h"
#include "tablechild.h"

#include <tableset.h>

SampleDatabase::SampleDatabase() : Nut::Database(),
    m_childs(new Nut::TableSet<TableChild>(this))
{

}
