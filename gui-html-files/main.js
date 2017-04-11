var frameID = 0;

function refresh(){
    for(var i=0;i<6;i++){
        $('#screenshot'+(6-i+1)).attr('src',"file:///home/administrator/julia/build/output/screenshots/screenshot-"+(frameID)+".png");
    }
    frameID++;
}

$(document).ready(function(){
    refresh();
    setInterval('refresh()',3000);
});
