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

$(document).ready(function() {
    var name = null;
    if (!localStorage.getItem('user')) {
        while((name = prompt("Введите имя")) == null);
        localStorage.setItem('user', name);
    }

    $("#input-form").on('submit', function(e) {
        var user = localStorage.getItem('user'),
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
        e.preventDefault();
    });

    $('#input-form textarea').on('keyup', function(e) {
        var message = $('#message').val();
        while(message.length > 0 && message[message.length - 1] == '\n') {
            message = message.slice(0, -1);
        }
        if (e.which == 13 && message != '') {
            $("#input-form").submit();
        } else if (e.which == 13) {
            $("#message").val('');
        }
        e.preventDefault();
    });

    setInterval(render, 1000);
});