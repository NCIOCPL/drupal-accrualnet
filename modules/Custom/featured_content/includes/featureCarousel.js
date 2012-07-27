/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
jQuery(function ($) {
        // Get the li elements
        var li = $( '.featured-carousel-slides li' ).hide(),
            controls = $( '.featured-carousel-slides .slideshowControl' ),
            selectedIndex = -1,
            slideshowPause = false;
        
        function slideshowSelect( i ) {
            $( li[selectedIndex] ).hide();
            $( controls[selectedIndex] ).removeClass( 'selected' );
            
            $( li[i] ).show();
            $( controls[i] ).addClass( 'selected' );
            
            selectedIndex = i;
        }
        
        window.setInterval( function () {
            if ( !slideshowPause ) {
                var index = (selectedIndex + 1) % li.length;
                slideshowSelect( index );   
            }
            
        }, 15000 );
        
        // Show the first one
        slideshowSelect( 0 );
        
        $( '.slideshowControl' ).click(
            function ( event, ele ) {
                slideshowSelect( $( this ).index() );
                slideshowPause = true;
            });

        //$('.next-tip-button').click(
        //function (event, ele) {
        //   var index = (selectedIndex + 1) % li.length;
        //   slideshowSelect( index );
        //});
    });


