# test.h

## Get started

```bash
wget https://raw.githubusercontent.com/IncludeOnly/test.h/refs/heads/main/test.h
```

## Example

```c
<example code>
```

## If you really need to link

```bash
mv test.h test.c
cc -o libtest.so test.c -fPIC -DTEST_IMPLEMENTATION -shared
mv test.c test.h
```

## License

[MIT](./LICENSE)
