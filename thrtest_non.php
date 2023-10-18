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
    <a href="thrtest.cpp">thrtest.cpp</a><br>
    <a href="thrtest_non.js">thrtest_non.js</a><br>
    <a href="thrtest_non.wasm">thrtest_non.wasm</a><br>
    <pre>emcc thrtest.cpp -o thrtest_non.js -s "EXPORTED_RUNTIME_METHODS=['ccall']"</pre>
    <div id="textcontent"></div>
    <input type="button" value="Test" onclick="BtnTest()">
    <input type="button" value="Start" onclick="ThrStart()">
    <input type="button" value="Stop" onclick="ThrStop()">
    <input type="button" value="Status" onclick="ThrStatus()">

    <script type='text/javascript'>

        function Info(Msg)
        {
            document.getElementById("textcontent").innerHTML = document.getElementById("textcontent").innerHTML + Msg + "<br>";
        }
    
        function BtnTest()
        {
            Module.ccall("_Z7ThrTestv", null, null, null);
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
    <script type="text/javascript" src="thrtest_non.js"></script>
  </body>
</html>
