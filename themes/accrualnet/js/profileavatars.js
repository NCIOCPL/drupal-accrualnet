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

        $('.avatar-option').click(function() {
            var $target = $('.user-picture').children('a').children('img');
            $target.css('width', '200px');
            
            $target.attr('src', $(this).children('img').attr('src'));
        });
        
    });
}) (jQuery);
