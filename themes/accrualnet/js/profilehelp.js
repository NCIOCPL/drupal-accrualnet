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
        $('.password-strength').css('visibility', 'hidden');
        $('.password-field').click(function () {
           $(this).children('.password-strength').css('visibility', 'visible');
        });
        
        
        
        
        var $pathToTheme = Drupal.settings.pathToTheme;
        $('.accrualnet-user-profile-form-wrapper').find('.description').each(function () {
            var $help = $(this).html();
            $(this).html('<img src="/' + $pathToTheme + '/accrualnet-internals/images/global/help.png" title="' + $help + '" />');
            $(this).hover(function () {
                $(this).children('img').attr('src', '/' + $pathToTheme + '/accrualnet-internals/images/global/help-active.png');
            }, function () {
$(this).children('img').attr('src', '/' + $pathToTheme + '/accrualnet-internals/images/global/help.png');
            });
        });
        
        
    });
}) (jQuery);
