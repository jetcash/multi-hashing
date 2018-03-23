#include <node.h>
#include <node_buffer.h>
#include <v8.h>
#include <stdint.h>

extern "C" {
    #include "cryptonight.h"
}

using namespace node;
using namespace v8;

void cryptonight(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    HandleScope scope(isolate);

    bool fast = false;

    if (args.Length() < 1){
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "You must provide one argument.")));
        return;
    }
    
    if (args.Length() >= 2) {
        if(!args[1]->IsBoolean()) {
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Argument 2 should be a boolean")));
            return;
        }

        fast = args[1]->ToBoolean()->BooleanValue();
    }

    Local<Object> target = args[0]->ToObject();

    if(!Buffer::HasInstance(target)) {
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "Argument should be a buffer object.")));
        return;
    }

    char * input = Buffer::Data(target);
    char output[32];
    
    uint32_t input_len = Buffer::Length(target);

    if(fast)
        cryptonight_fast_hash(input, output, input_len);
    else
        cryptonight_hash(input, output, input_len);

    args.GetReturnValue().Set(Buffer::Copy(isolate, (char*) &output, 32).ToLocalChecked());

}

void init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "cryptonight", cryptonight);
}

NODE_MODULE(multihashing, init)
