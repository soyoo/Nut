

# Nut

## Build result
| Branch        | Status        |
| ------------- |:-------------:|
| master        | [![Build Status](https://travis-ci.org/HamedMasafi/Nut.svg?branch=master)](https://travis-ci.org/HamedMasafi/Nut) |
| dev           | [![Build Status](https://travis-ci.org/HamedMasafi/Nut.svg?branch=dev)](https://travis-ci.org/HamedMasafi/Nut) |

[![Codacy 
Badge](https://api.codacy.com/project/badge/Grade/f3802610beb946068f6cd2c2b6608a8b)](https://www.codacy.com/app/HamedMasafi/Nut?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=HamedMasafi/Nut&amp;utm_campaign=Badge_Grade)

## Advanced, Powerful and easy to use ORM for Qt5


## Features:

 - Easy to use
 - Support PosgtreSQL, MySQL, SQLite and Microsoft Sql Server
 - Automatically create and update database
 - IDE auto complete support, No hard-code nedded
 - Table join detect 
 - Supported types:

| Type  | Sqlite | MySql  | Postgresql| Ms Sql server |
|--------|--------|--------|--------|--------|
|  QBitArray  |  BLOB  |  VARBINARY  |  BYTEA  |  VARBINARY (MAX)  |
|  QByteArray  |  BLOB  |  BLOB  |  BYTEA  |  VARBINARY (MAX)  |
|  QChar  |  NCHAR(1)  |  CHAR(1)  |  CHAR(1)  |  CHAR(1)  |
|  QColor  |  TEXT  |  TEXT  |  TEXT  |  TEXT  |
|  QDate  |  DATE  |  DATE  |  DATE  |  DATE  |
|  QDateTime  |  DATETIME  |  DATETIME  |  TIMESTAMP  |  DATETIME  |
|  QJsonArray  |  TEXT  |  TEXT  |  JSON  |  TEXT  |
|  QJsonDocument  |  TEXT  |  TEXT  |  JSON  |  TEXT  |
|  QJsonObject  |  TEXT  |  TEXT  |  JSON  |  TEXT  |
|  QJsonValue  |  TEXT  |  TEXT  |  JSON  |  TEXT  |
|  QLine  |  TEXT  |  TEXT  |  LINE  |  TEXT  |
|  QLineF  |  TEXT  |  TEXT  |  LINE  |  TEXT  |
|  QPoint  |  TEXT  |  POINT  |  POINT  |  GEOMETRY  |
|  QPointF  |  TEXT  |  POINT  |  POINT  |  GEOMETRY  |
|  QPolygon  |  TEXT  |  POLYGON  |  POLYGON  |  TEXT  |
|  QPolygonF  |  TEXT  |  POLYGON  |  POLYGON  |  TEXT  |
|  QRect  |  TEXT  |  TEXT  |  BOX  |  TEXT  |
|  QRectF  |  TEXT  |  TEXT  |  BOX  |  TEXT  |
|  QSize  |  TEXT  |  TEXT  |  TEXT  |  TEXT  |
|  QSizeF  |  TEXT  |  TEXT  |  TEXT  |  TEXT  |
|  QString  |  TEXT  |  TEXT  |  TEXT  |  NVARCHAR(MAX)  |
|  QStringList  |  TEXT[^*]  |  TEXT  |  TEXT[]  |  TEXT  |
|  QTime  |  TIME  |  TIME  |  TIME  |  TIME  |
|  QUrl  |  TEXT  |  TEXT  |  TEXT  |  TEXT  |
|  QUuid  |  TEXT  |  VARCHAR(64)  |  UUID  |  UNIQUEIDENTIFIER  |
|  bool  |  BOOLEAN  |  BOOLEAN  |  BOOLEAN  |  BIT  |
|  char  |  TINYINT  |  CHAR(1)  |  CHAR(1)  |  CHAR(1)  |
|  double  |  DOUBLE  |  REAL  |  REAL  |  REAL  |
|  float  |  FLOAT  |  FLOAT  |  FLOAT  |  FLOAT(24)  |
|  int  |  INT  |  INT  |  INTEGER  |  INT  |
|  long  |  MEDIUMINT  |  BIGINT  |  BIGINT  |  BIGINT  |
|  qlonglong  |  BIGINT  |  BIGINT  |  BIGINT  |  BIGINT  |
|  qulonglong  |  BIGINT UNSIGNED  |  BIGINT  |  BIGINT  |  BIGINT  |
|  short  |  SMALLINT  |  SMALLINT  |  SMALLINT  |  SMALLINT  |
|  signed char  |  TINYINT  |  TINYINT  |  SMALLINT  |  TINYINT  |
|  uchar  |  TINYINT UNSIGNED  |  TINYINT  |  SMALLINT  |  TINYINT  |
|  uint  |  INT UNSIGNED  |  INT  |  INTEGER  |  INT  |
|  ulong  |  MEDIUMINT UNSIGNED  |  BIGINT  |  BIGINT  |  BIGINT  |
|  ushort  |  SMALLINT UNSIGNED  |  SMALLINT  |  SMALLINT  |  SMALLINT  |

[^*]: Using internal store/restore serialization


## Sample Codes
### Read data from database:

```cpp
auto q = db.posts()->createQuery();
q->setWhere(Post::idField() == postId);
auto posts = q->toList();
// now posts is a QList<Post*> contain all posts in
//  database that has id equal to postId variable
auto post = q->first();
// post is first row in database that its id is equal to postId
```

### Adding to database:
```cpp
Post *newPost = new Post;
newPost->setTitle("post title");

db.posts()->append(newPost);

for(int i = 0 ; i < 3; i++){
    Comment *comment = new Comment;
    comment->setMessage("comment #" + QString::number(i));

    newPost->comments()->append(comment);
}
db.saveChanges();
```

### Modify database data:
```cpp
auto q = db.posts()->createQuery();
q->setWhere(Post::idField() == postId);
Post *post = q->first();

if(post) {
    post->setTitle("new name");
    db.saveChanges();
} else {
    qWarning("No post found!");
}
```

### Donate
Butcoin address: 1Dn1WHKkaxanXe4cTGDk4cFRRABxLUpEVj


![Wallet addresst](btc-qr.png)

For more information read [Wiki](wiki).
