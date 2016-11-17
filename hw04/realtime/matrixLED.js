    var socket;
    var firstconnect = true,
        i2cNum  = "0x70",
	disp = [];
    var selectedColor= "green";
var cleararray = [0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
];
var dataarray = [0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
];
// Create a matrix of LEDs inside the <table> tags.
var matrixData;
for(var j=7; j>=0; j--) {
	matrixData += '<tr>';
	for(var i=0; i<8; i++) {
	    matrixData += '<td><div class="LED" id="id'+i+'_'+j+
		'" onclick="LEDclick('+i+','+j+')">'+
		i+','+j+'</div></td>';
	    }
	matrixData += '</tr>';
}
$('#matrixLED').append(matrixData);

// The slider controls the overall brightness
$("#slider1").slider({min:0, max:15, slide: function(event, ui) {
	socket.emit("i2cset",  {i2cNum: i2cNum, i: ui.value+0xe0, disp: 1});
    }});

// Send one column when LED is clicked.
function LEDclick(i, j) {
//	alert(i+","+j+" clicked");
    //isp[i] ^= 0x1<<j;
    currentElement=document.getElementById('id'+i+'_'+j)
    //socket.emit('i2cset', {i2cNum: i2cNum, i: 2*i, disp: '0x'+disp[i].toString(16)});
//    if(disp[i]>>j&0x1 === 1 || disp[2*i+1]>>j&0x1 === 1) {
    if(currentElement.classList.contains(selectedColor)) {
        $('#id'+i+'_'+j).removeClass(selectedColor);
        updateRow(i,selectedColor,j,0);
    } else {
        $('#id'+i+'_'+j).addClass(selectedColor);
        updateRow(i,selectedColor,j,1);
    }
    if(currentElement.classList.contains('red') && currentElement.classList.contains('green')) {
        $('#id'+i+'_'+j).addClass('orange');
    }
    else {
        $('#id'+i+'_'+j).removeClass('orange');
    }   
}

function updateRow(rowNum, color, colnum, state) {
    if(color==='green')
    {
        rowNum=rowNum*2;
    }
    else if(color==='red')
    {
        rowNum=rowNum*2+1;
    }
    if(state===1) {
    //disp[rowNum] ^= 0x1<<colnum;
    disp[rowNum] = disp[rowNum] | 0x1<<colnum;
        socket.emit('i2cset', {i2cNum: i2cNum, i: rowNum, disp: '0x'+disp[rowNum].toString(16)});
    }
    else {
        disp[rowNum] = disp[rowNum] & ~(0x1<<colnum);
        socket.emit('i2cset', {i2cNum: i2cNum, i: rowNum, disp: '0x'+disp[rowNum].toString(16)});

    }
}

function clearMatrix() {
    for(var i=0;i<17;i++){
    socket.emit('i2cset', {i2cNum: i2cNum, i: i, disp: '0x00'.toString(16)});
    }
    for (i = 0; i < disp.length; i++) {
    // j cycles through each bit
        for (j = 0; j < 8; j++) {
                $('#id' + i + '_' + j).removeClass("orange");
                $('#id' + i + '_' + j).removeClass("green");
                $('#id' + i + '_' + j).removeClass("red");
            }
        }
        disp = [];
    }
    function connect() {
      if(firstconnect) {
        socket = io.connect(null);

        // See https://github.com/LearnBoost/socket.io/wiki/Exposed-events
        // for Exposed events
        socket.on('message', function(data)
            { status_update("Received: message " + data);});
        socket.on('connect', function()
            { status_update("Connected to Server"); });
        socket.on('disconnect', function()
            { status_update("Disconnected from Server"); });
        socket.on('reconnect', function()
            { status_update("Reconnected to Server"); });
        socket.on('reconnecting', function( nextRetry )
            { status_update("Reconnecting in " + nextRetry/1000 + " s"); });
        socket.on('reconnect_failed', function()
            { message("Reconnect Failed"); });

        socket.on('matrix',  matrix);

    socket.emit('i2cset', {i2cNum: i2cNum, i: 0x21, disp: 1}); // Start oscillator (p10)
    socket.emit('i2cset', {i2cNum: i2cNum, i: 0x81, disp: 1}); // Disp on, blink off (p11)
    socket.emit('i2cset', {i2cNum: i2cNum, i: 0xe7, disp: 1}); // Full brightness (page 15)
    /*
	i2c_smbus_write_byte(file, 0x21); 
	i2c_smbus_write_byte(file, 0x81);
	i2c_smbus_write_byte(file, 0xe7);
    */
        // Read display for initial image.  Store in disp[]
        socket.emit("matrix", i2cNum);

        firstconnect = false;
      }
      else {
        socket.socket.reconnect();
      }
    }

    function disconnect() {
      socket.disconnect();
    }

    // When new data arrives, convert it and display it.
    // data is a string of 16 values, each a pair of hex digits.
    function matrix(data) {
        var i, j;
        disp = [];
        //        status_update("i2c: " + data);
        // Make data an array, each entry is a pair of digits
        data = data.split(" ");
        //        status_update("data: " + data);
        // Every other pair of digits are Green. The others are red.
        // Ignore the red.
        // Convert from hex.
        for (i = 0; i < data.length; i += 2) {
            disp[i / 2] = parseInt(data[i], 16);
        }
        //        status_update("disp: " + disp);
        // i cycles through each column
        for (i = 0; i < disp.length; i++) {
            // j cycles through each bit
            for (j = 0; j < 8; j++) {
                if (((disp[i] >> j) & 0x1) === 1) {
                    $('#id' + i + '_' + j).addClass(selectedColor);
                } else {
                    $('#id' + i + '_' + j).removeClass(selectedColor);
                }
            }
        }
    }

    function selectColor(color){

        if(color=="red"){
            selectedColor="red";
            
            $('#clickableGreen').removeClass("selectedBox")
            $('#clickableGreen').addClass("unSelectedBox");
            $('#clickableOrange').removeClass("selectedBox")
            $('#clickableOrange').addClass("unSelectedBox");
            $('#clickableRed').removeClass("unSelectedBox")
            $('#clickableRed').addClass("selectedBox");
        }
        else {
            selectedColor="green";
            $('#clickableRed').removeClass("selectedBox")
            $('#clickableRed').addClass("unSelectedBox");
            $('#clickableOrange').removeClass("selectedBox")
            $('#clickableOrange').addClass("unSelectedBox");
            $('#clickableGreen').removeClass("unSelectedBox")
            $('#clickableGreen').addClass("selectedBox");
        }
    }
    function status_update(txt){
	$('#status').html(txt);
    }

    function updateFromLED(){
      socket.emit("matrix", i2cNum);    
    }

connect();

$(function () {
    // setup control widget
    $("#i2cNum").val(i2cNum).change(function () {
        i2cNum = $(this).val();
    });
});
