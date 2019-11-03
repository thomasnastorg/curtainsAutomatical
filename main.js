requirejs.config({
    baseUrl: 'http://192.168.1.107/lib',
    paths: {
        // the left side is the module ID,
        // the right side is the path to
        // the jQuery file, relative to baseUrl.
        // Also, the path should NOT include
        // the '.js' file extension. This example
        // is using jQuery 1.9.0 located at
        // js/lib/jquery-1.9.0.js, relative to
        // the HTML page.
        jquery: 'http://192.168.1.107/lib/jquery.min.js',
        main : '../main',
        index :'http://192.168.1.107/lib/tplink-smarthome-api/lib/index',
/*        client : 'http://192.168.1.107/lib/tplink-smarthome-api/lib/client',
        utils : 'http://192.168.1.107/lib/tplink-smarthome-api/lib/utils',*/
      }

});

//requirejs(['http://192.168.1.107/lib/display.js'])
requirejs(['http://192.168.1.107/lib/tplink-smarthome-api/lib/index.js'])



/*require(["client"], function(client) {
    console.log("client loaded OK.");
});

require(["utils"], function(utils) {
    console.log("utils loaded OK.");
});*/
