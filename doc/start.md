### Read data from database:

```cpp
auto posts = db.posts()->query()
    ->where(Post::idField() == postId)
    ->toList();
// now posts is a QList<Post*> contain all posts in
//  database that has id equal to postId variable
auto post = q->first();
// post is first row in database that its id is equal to postId
```

### Adding to database:
```cpp
auto newPost = Nut::create<Post>();
newPost->setTitle("post title");

db.posts()->append(newPost);

for(int i = 0 ; i < 3; i++){
    // Below line same as new Comment in non shared pointer mode 
    // or QSharedPointer<Comment>(new Comment) in shared_pointer mode

    auto comment = Nut::create<Comment>(); 
    comment->setMessage("comment #" + QString::number(i));

    newPost->comments()->append(comment);
}
db.saveChanges();
```

### Modify database data:
```cpp
auto post = db.posts()->query()
    ->where(Post::idField() == postId)
    ->first();

if(post) {
    post->setTitle("new name");
    db.saveChanges();
} else {
    qWarning("No post found!");
}
```

