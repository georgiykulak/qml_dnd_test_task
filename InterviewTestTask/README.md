## Setup environment & launch project

```bash
# Python3.7 Cmake, Qt5.15 required

# Run server:
$ python server/server.py
```

## TODO

### Complete the Qt-application with client code.
Client must implement behavior as on the attached video(Application.mov)

#### What is already implemented
Server side is already implemented. Client should send message `"next"` to get color for the new element and message `"stop"` to close connection.

###ALL CONFIG DATA ARE PROVIDED IN Conf.h

#### What needs to be implemented
You need to implement class `Client`.

You are free in the other methods implementation, other classes implementation, QML files changing.

#### Requirements for the client:
 
1. Client must have drag and drop functionality for moving elements. Element should be inserted between others. NOT SWAPPED!
2. Client must have "change color" functionality.
3. Client must have loading model dialog to avoid user interractions during downloading data.
4. Data downloading mustn't freeze UI thread
5. User should be able to cancel downloading
6. Client should handle connection problems.

### Good luck!