
open Serbet.Endpoint; //A simple way to set up an Express.js server on top of Node.js using ReasonML.


open Async;

// to get " hello world" at path /hello
let hello =
  Serbet.endpoint({
    verb: GET,
    path: "/hello",
    handler: _req => {
/// @@ evaluates the result of its right-hand side, and passes the result as the only argument to whatever function is on the left-hand side.
      async @@ OkString("Hello world");
    },
  });


module HelloEndpoint = {
    //Decco is a language extension that automatically generates encoders and decoders for us.
  [@decco.decode]
  type params = {name: string};
  let endpoint =
    Serebet.endpoint({
      verb: Get,
      // parameterized path to deal with params
      path: "/hello/:name",
      //a special function that takes in an express request and should return a promise of a response type
      handler: req => {
          //get the params off of the path
        let%Async params = req.requireParams(params_decode);
        // okString >> respond OK 200 with a string
        okString("Hello " ++ params.name)->async;
      },
    });
};

let app =
  Serbet.application(
    ~port=3110,
    [hello, HelloEndpoint.endpoint]
  );
