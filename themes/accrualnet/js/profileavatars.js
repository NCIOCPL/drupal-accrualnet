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
        $('#edit-picture-upload').click(function () {
            
        });

        $('.avatar-option').click(function() {
            var $target = $('.user-picture').children('a').children('img');
            var $newsrc = $(this).children('img').attr('src');
            $target.css('width', '200px');
            $target.attr('src', $newsrc);

            $('input#edit-picture-upload').val($(this).attr('id').toString() + ".png");
        });
        

    });
}) (jQuery);
