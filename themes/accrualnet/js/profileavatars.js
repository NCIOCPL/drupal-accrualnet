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
        var $pathToTheme = Drupal.settings.pathToTheme;
        var $target = $('.user-picture').children('a').children('img');
         
        $('<p class="user-img-or">Or</p>').insertAfter($('.imagecrop-button'));
        $('<p class="user-img-or">Or</p>').insertAfter($('.form-item-files-picture-upload'));
         
         
        $('input#edit-picture-upload').change(function () {
            $target.attr('src', '/' + $pathToTheme + '/accrualnet-internals/images/needtoupload.jpg');
            $('select#edit-avatar-image-und').val('_none');
            $('.picked').removeClass('picked');
        });
        
        $('.picked').each(function () {
            $target.attr('src', $(this).children('img').attr('src'));
            $target.css('width', '200px');
            $('input#edit-picture-upload').val('');
            $('.imagecrop-button').css('display', 'none');
            $('.imagecrop-button').next().css('visibility', 'hidden');
        });
        
        $('.imagecrop-button').click(function () {
            $target.attr('src', Drupal.settings.avatarfile);
            $('select#edit-avatar-image-und').val('_none');
            $('.picked').removeClass('picked');
            $('input#edit-picture-upload').val('');
        });

        $('.avatar-option').click(function() {
            var $newsrc = $(this).children('img').attr('src');
            $target.css('width', '200px');
            $target.attr('src', $newsrc);
            
            var $gender = $(this).attr('title');
            var $color = $(this).attr('id');
            
            $('select#edit-avatar-image-und').children().each(function () {
                if ($(this).html() == ($gender + '/' + $color)) {
                    $('select#edit-avatar-image-und').val($(this).val());
                }
            });
            
            $('input#edit-picture-upload').val('');
            
            $('.picked').removeClass('picked');
            $(this).addClass('picked');
            
            $('.imagecrop-button').css('display', 'none');
            $('.imagecrop-button').next().css('visibility', 'hidden');
            
        });
        
                $('span.avatar-option').keyup(function (e) {
                    var key = e.charCode ? e.charCode : e.keyCode ? e.keyCode : 0;
        if(key == 13 || key == 32) {
                        var $newsrc = $(this).children('img').attr('src');
            $target.css('width', '200px');
            $target.attr('src', $newsrc);
            
            var $gender = $(this).attr('title');
            var $color = $(this).attr('id');
            
            $('select#edit-avatar-image-und').children().each(function () {
                if ($(this).html() == ($gender + '/' + $color)) {
                    $('select#edit-avatar-image-und').val($(this).val());
                }
            });
            
            $('input#edit-picture-upload').val('');
            
            $('.picked').removeClass('picked');
            $(this).addClass('picked');
            
            $('.imagecrop-button').css('display', 'none');
            $('.imagecrop-button').next().css('visibility', 'hidden');
        }

        });
        

    });
}) (jQuery);
