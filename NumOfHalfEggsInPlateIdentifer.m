function A3_2585271(input_image)

    function output_image = segmantation(input_image) %segmantation function
    
        smoth_img=imboxfilt(input_image,3); % smothing the original image with 3x3 box(averaging) filter 
        
        Red = smoth_img(:, :, 1);  % intitializng the red chanel 
        Green = smoth_img(:, :, 2);  % initializg the green chanel
        Blue = smoth_img(:, :, 3); % initializng the blue channel
        
        yellow_thershold = (Red >= 222) & (Green >= 145 & Green < 230) & (Blue <= 105);
        % Thresholding based on color which is Red value equal and greather than
        % 222, green value between 145 and 230 and blue values less than 105
        
        Struct1 = strel('disk',13); % structuring element for closing operation
        Struct2 = strel('disk',24); % structuring element for the other operations
        
        Closed_image = imclose(yellow_thershold,Struct1); % closing image with struct1 for filling the small gaps and connecting 
        Opened_image = imopen(Closed_image,Struct2); % opeening the closed image wtih struct2 for elimating small objects 
        Filled_image = imfill(Opened_image,'holes'); % filling the holes in the opended image
        Eroded_image = imerode(Filled_image,Struct2); % eroding the filled image for trying disconnecet connected eggs
        output_image=Eroded_image;
    
        figure; % showing the segmantation steps
        subplot(2,3,1);imshow(smoth_img);title("Smothed Image");
        subplot(2,3,2);imshow(yellow_thershold);title("Thresholded image");
        subplot(2,3,3);imshow(Closed_image);title("Closed Image");
        subplot(2,3,4);imshow(Opened_image);title("Opened Image");
        subplot(2,3,5);imshow(Filled_image);title("Filled Image");
        subplot(2,3,6);imshow(output_image);title("Segmanted Image");
    
    end
    
    function numOFegg = counting_egg(segmented_image)
        segmanted=segmented_image;
        [~, num] = bwlabel(segmanted,4); %doing connected component extraction by 4-connectivity
        numOFegg=num/2; %since we are dealing with half eggs we should show the correct egg number
    
    end

image=input_image;
segmantedimage=segmantation(image); %calling the segmantation function
numofegg= counting_egg(segmantedimage); % calling the counting eggs function
figure; % showing the segmanted image and number of egg
imshow(segmantedimage);title(["Number Of eggs in the image is " num2str(numofegg)]);
end
