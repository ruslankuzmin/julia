var frameID = 0;
var isPlayed = true;

function refresh(){
    for(var i=0;i<6;i++){
        $("#screenshot"+(6-i+1)).attr('src',"file:///home/administrator/julia/build/output/screenshots/screenshot-"+(frameID)+".png");
    }
    frameID++;
}

function changePlayState(){
    isPlayed = !isPlayed;
    if( isPlayed ){
        $("#playButton").attr("src","images/start.png");
        $("#playButtonText").html("Продолжить");
        //channel.objects.control.stop();
    }else{
        $("#playButton").attr("src","images/stop.png");
        $("#playButtonText").html("Сделать остановку");
        //channel.objects.control.play();
    }
}

$(document).ready(function(){
    window.channel = new QWebChannel(qt.webChannelTransport, function(channel) {
        //connect to the changed signal of a property
        channel.objects.control.refresh.connect(function() {
            alert(1);
        });
    });

    changePlayState();
    $("#playButton,#playButtonText").click(function() {
        changePlayState();
    });
    refresh();
    setInterval('refresh()',3000);
});

