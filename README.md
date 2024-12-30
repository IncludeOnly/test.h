# test.h

## Get started

```bash
wget https://raw.githubusercontent.com/IncludeOnly/test.h/refs/heads/main/test.h
```

## Example

`test/main.c`
```c
#define TEST_IMPLEMENTATION
#include "test.h"

int main(){
    LOAD_TEST("test_checkmate");
    LOAD_TEST("test_stalemate");
    

    START_TESTS
        RUN_TEST(test_checkmate),
        RUN_TEST(test_stalemate)
    END_TESTS
}
```

`test/test_checkmate.c`
```c
#include "test.h"

int test_checkmate(const char* fen, bool expected){
    Board board;
    BoardLoadFen(&board, fen);

    if(IsCheckmate(board) != expected){
        FAIL("Expected %s for fen %s", (expected) ? "true" : "false", fen);
        return 0;
    }

    SUCC("Passed for fen %s", fen);
    return 1;
}
```

`test/test_checkmate.ctd`
```text
"fen1", true
"fen2", false
# "fen3", true
```

## If you really need to link

```bash
mv test.h test.c
cc -o libtest.so test.c -fPIC -DTEST_IMPLEMENTATION -shared
mv test.c test.h
```

## License

[MIT](./LICENSE)
