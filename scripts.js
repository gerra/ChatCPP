var entryPoint = 'http://localhost:2323';
function send(user, message, callback) {
    $.ajax({
        url: entryPoint+'/messages',
        //dataType: 'json',
        type: 'POST',
        data: JSON.stringify({
            user: user,
            message: message
        }),
        success: callback
    });
}
function get(callback) {
    $.ajax({
        url: entryPoint+'/messages',
        dataType: 'json',
        type: 'GET',
        success: callback
    });
}
function render() {
    get(function(data) {
        var response = '';
        $.each(data, function(key, val) {
            response += '<li>'+val.user+': '+val.message+'</li>';
        });
        $("#list").html(response);
    });
}
function sendHandler() {
    var user = 'Mike',
        message = $('#message').val();
    if (message != '') {
        $("#input-form button").attr('disabled','disabled');
        $("#list").append('<li>'+user+': '+message+'</li>');
        send(user, message, function() {
            $("#message").val('');
            $("#input-form button").removeAttr('disabled');
        });
    } else {
        alert("Введите текст!");
    }
}
$(document).ready(function() {
    $("#input-form").on('submit', function(e) {
        sendHandler();
        e.preventDefault();
    });
    $('#input-form textarea').on('keyup', function(e) {

        if (e.which == 13) {
            $("#input-form").submit();
        }
        e.preventDefault();
    });
    setInterval(render, 1000);
});