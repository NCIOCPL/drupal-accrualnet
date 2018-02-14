/***
 * Added By: Lauren
 * Added On: July 16, 2012
 * 
 * Last Edited By: Lauren
 * Last Edited On: July 17, 2012
 * 
 * This darkens the BORDER-COLOR of an INPUT box when editing it.
 ***/

(function ($) {
    $(document).ready(function() {

        $('input.password-field').keyup(function () {
            if ($(this).val().length < 1) {
                $(this).parent().children('.password-strength').css('visibility', 'hidden');
            } else {
                $(this).parent().children('.password-strength').css('visibility', 'visible');
            }
        });
        
        //$('legend#edit-field-occupation-und-select').prepend($('label[for="edit-field-occupation-und-select"]'));
        
        /*
        $('#edit-roles').prepend($('#edit-roles').prev());
        //$('tsst').insertBefore($('#edit-roles').children('label').next());
        $('<p>tsst</p>').insertBefore($('#edit-roles').children('label').next())
        $('.form-item-roles').css('border', '1px solid red');
        $('<fieldset><legend>Roles</legend>').insertBefore($('.form-item-roles'));
        //$('<p>tests</p>').insertBefore($('#edit-roles').parent().next());
        $('<p>what</p></fieldset>').insertAfter($('.form-item-roles'));
        */
        
        var $pathToTheme = Drupal.settings.pathToTheme;
        $('.description').each(function () {
            var $help = $(this).html();
            $(this).html('<img alt="' + $help + '" src="/' + $pathToTheme + '/accrualnet-internals/images/global/help.png" title="' + $help + '" />');
            $(this).hover(function () {
                $(this).children('img').attr('src', '/' + $pathToTheme + '/accrualnet-internals/images/global/help-active.png');
            }, function () {
$(this).children('img').attr('src', '/' + $pathToTheme + '/accrualnet-internals/images/global/help.png');
            });
        });
        
        
    });
}) (jQuery);
