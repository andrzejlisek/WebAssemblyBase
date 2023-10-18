<?php
header("Cross-Origin-Embedder-Policy: require-corp");
header("Cross-Origin-Opener-Policy: same-origin");
?>
<!doctype html>
<html lang="en-us">
  <head>
    <meta charset="utf-8">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
    <title>Emscripten-Generated Code</title>
    <style>
         div { border-style:solid; } 
    </style>
  </head>
  <body>
    <pre>emcc hello.cpp -o hello.js -s NO_EXIT_RUNTIME=1 -s "EXPORTED_RUNTIME_METHODS=['ccall']" -sWASM_WORKERS</pre>
    <div id="textcontent"></div>
    <input type="button" value="Test" onclick="BtnTest()">
    <input type="button" value="Start" onclick="ThrStart()">
    <input type="button" value="Stop" onclick="ThrStop()">
    <input type="button" value="Status" onclick="ThrStatus()">

    <script type='text/javascript'>

        // Create list of object members - https://flaviocopes.com/how-to-list-object-methods-javascript/
        function getMethods(obj)
        {
            let Names = Object.getOwnPropertyNames(obj);
            let MemberList = [];
            for (var Item in Names)
            {
                let Nx = Names[Item];
                if (obj.hasOwnProperty(Nx))
                {
                    if (Nx[0] == '_')
                    {
                        MemberList.push(Nx);
                    }
                }
            }
            return MemberList;
        }
        function Info(Msg)
        {
            document.getElementById("textcontent").innerHTML = document.getElementById("textcontent").innerHTML + Msg + "<br>";
        }
    
    
        function CallbackTestNum(ValI)
        {
            let ValO = 255 - ValI;
            Info("CallbackTestNum in: " + ValI);
            Info("CallbackTestNum out: " + ValO);
            return ValO;
        }

        function CallbackTestStr(ValI)
        {
            let ValO = "World";
            Info("CallbackTestStr in: " + ValI);
            Info("CallbackTestStr out: " + ValO);
            return ValO;
        }
    
        function BtnTest()
        {
            Info(getMethods(Module).join("<br>"));

            const result = Module.ccall(
              "_Z10myFunctioniPPc", // name of C function
              null, // return type
              null, // argument types
              null, // arguments
            );

            Info("Integer test start");
            Info("fib(6)=" + Module.ccall("_Z3fibi", "number", ["number"], [6]));
            Info("Integer test stop");

            Info("String test start");
            Info("StrTest1()=" + Module.ccall("_Z8StrTest1v", "string", null, null));
            Info("StrTest2()=" + Module.ccall("_Z8StrTest2Pc", "string", ["string"], ["hello WORLD"]));
            Info("String test stop");
    
            Info("Callback test start");
            for (I = 0; I <= 4; I++)
            {
                Info("Javascript callback " + I + " invoke");
                Info("Javascript callback " + I + " return: " + Module.ccall("_Z12CallbackTesti", "number", ["number"], [I]));
            }
            Info("Callback test stop");
    
        }
    
        function ThrStart()
        {
            Info("Thread start " + Module.ccall("_Z8ThrStartv", "number", null, null));
        }
        function ThrStop()
        {
            Info("Thread stop " + Module.ccall("_Z7ThrStopv", "number", null, null));
        }
        function ThrStatus()
        {
            Info("Thread status " + Module.ccall("_Z9ThrStatusv", "number", null, null));
        }
    
      var Module = {
        print: (function() {
          var element = document.getElementById('output');
          if (element) element.value = ''; // clear browser cache
          return function(text) {
            if (arguments.length > 1) text = Array.prototype.slice.call(arguments).join(' ');
            Info("Printf: " + text);
          };
        })(),
        setStatus: (text) => {
          Info("setStatus: " + text);
        },
        totalDependencies: 0,
        monitorRunDependencies: (left) => {
          this.totalDependencies = Math.max(this.totalDependencies, left);
          Module.setStatus(left ? 'Preparing... (' + (this.totalDependencies-left) + '/' + this.totalDependencies + ')' : 'All downloads complete.');
        }
      };
      Module.setStatus('Downloading...');
      window.onerror = (event) => {
        Module.setStatus('Exception thrown, see JavaScript console');
        Module.setStatus = (text) => {
          if (text) Info('[post-exception status] ' + text);
        };
      };
    </script>
    <script async type="text/javascript" src="hello.js"></script>
  </body>
</html>
