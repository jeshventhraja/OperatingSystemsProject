gcc read_write.c -pthread -o reader
./reader
python reader_writer.py
