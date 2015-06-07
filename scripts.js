var entryPoint = 'http://localhost:2323';
function send(user, message, callback) {
    $.ajax({
        url: entryPoint+'/messages',
        dataType: 'json',
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
    $("#input-form").on('submit', function(e) {
        var user = 'Mike',
            message = $('#message').val();
        $("#input-form button").attr('disabled','disabled');
        send(user, message, function() {
            $("#message").val('');
            $("#input-form button").removeAttr('disabled');
        });
        e.preventDefault();
    });
    setInterval(render, 1000);
});