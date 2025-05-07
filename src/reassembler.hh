#pragma once

#include "byte_stream.hh"

class Reassembler {
public:
    // Construct Reassembler to write into given ByteStream.
    explicit Reassembler(ByteStream&& output)
        : output_(std::move(output)),
          capacity(output_.writer().available_capacity()),
          unAssembleBytes(0),
          firstUnAcceptable(capacity),
          currentIndex(0),
          endIndex(0),
          end(false),buffer(capacity,'\0'),judgeBuffer(capacity,false){
       
    }

    // Insert a new substring to be reassembled into a ByteStream.
    void insert(uint64_t first_index, std::string data, bool is_last_substring);

    // How many bytes are stored in the Reassembler itself?
    uint64_t count_bytes_pending() const;

    // Access output stream reader
    Reader& reader() { return output_.reader(); }
    const Reader& reader() const { return output_.reader(); }

    // Access output stream writer, but const-only (can't write from outside)
    const Writer& writer() const { return output_.writer(); }

private:
    ByteStream output_;
    uint64_t capacity;
    uint64_t unAssembleBytes;
    uint64_t firstUnAcceptable;
    uint64_t currentIndex;
    uint64_t endIndex;
    bool end;
    std::deque<char> buffer;
    std::deque<bool> judgeBuffer;
};