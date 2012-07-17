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
        $('.description')
        
    });
}) (jQuery);
