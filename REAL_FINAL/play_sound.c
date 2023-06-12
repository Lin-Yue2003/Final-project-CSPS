#include <stdio.h>
#include <pthread.h>
#include <AudioToolbox/AudioToolbox.h>
#include "play_sound.h"
void* printThread(void* arg){
    printf("\033[1m"); 
    printf("\033[31mW ");
    fflush(stdout);
    sleep(1); // Adjust the sleep duration as needed           
    printf("\033[32mE ");
    fflush(stdout);
    sleep(1); // Adjust the sleep duration as needed   
    printf("\033[33mL ");
    fflush(stdout);
    sleep(1); // Adjust the sleep duration as needed   
    printf("\033[34mC ");
    fflush(stdout);
    sleep(1); // Adjust the sleep duration as needed
    printf("\033[35mO ");
    fflush(stdout);
    sleep(1); // Adjust the sleep duration as needed    
    printf("\033[36mM ");
    fflush(stdout);
    sleep(1); // Adjust the sleep duration as needed 
    printf("\033[31mE ");
    fflush(stdout);
    sleep(1); // Adjust the sleep duration as needed
    printf("\033[32m！\033[0m");
    fflush(stdout);
    sleep(1); // Adjust the sleep duration as needed   
    return NULL;
}
void play_sound_door(){
    // Specify the path to the audio file
    CFURLRef soundURL = CFURLCreateWithFileSystemPath(NULL, CFSTR("FamilyMart_Ringtone Piano.wav"), kCFURLPOSIXPathStyle, false);

    // Create a system sound ID
    SystemSoundID soundID;
    AudioServicesCreateSystemSoundID(soundURL, &soundID);

    // Create a separate thread for printing
    pthread_t thread;
    pthread_create(&thread, NULL, printThread, NULL);

    // Play the sound
    AudioServicesPlaySystemSound(soundID);

    // Wait for the sound to finish playing
    CFRunLoopRunInMode(kCFRunLoopDefaultMode, 8, false);

    //CFRunLoopRunInMode(kCFRunLoopDefaultMode, 8, false);

    // Clean up resources
    AudioServicesDisposeSystemSoundID(soundID);
    CFRelease(soundURL);
}
void play_sound_scan(){
    // Specify the path to the audio file
    CFURLRef soundURL = CFURLCreateWithFileSystemPath(NULL, CFSTR("scan.wav"), kCFURLPOSIXPathStyle, false);

    // Create a system sound ID
    SystemSoundID soundID;
    AudioServicesCreateSystemSoundID(soundURL, &soundID);

    // Play the sound
    AudioServicesPlaySystemSound(soundID);

    // Wait for the sound to finish playing
    CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0.3, false);

    // Clean up resources
    AudioServicesDisposeSystemSoundID(soundID);
    CFRelease(soundURL);
}
void play_sound_delete(){
    // Specify the path to the audio file
    CFURLRef soundURL = CFURLCreateWithFileSystemPath(NULL, CFSTR("delete.wav"), kCFURLPOSIXPathStyle, false);

    // Create a system sound ID
    SystemSoundID soundID;
    AudioServicesCreateSystemSoundID(soundURL, &soundID);

    // Play the sound
    AudioServicesPlaySystemSound(soundID);

    // Wait for the sound to finish playing
    CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0.2, false);

    // Clean up resources
    AudioServicesDisposeSystemSoundID(soundID);
    CFRelease(soundURL);
}
void play_sound_cash_register(){
    // Specify the path to the audio file
    CFURLRef soundURL = CFURLCreateWithFileSystemPath(NULL, CFSTR("Cash_Register.wav"), kCFURLPOSIXPathStyle, false);

    // Create a system sound ID
    SystemSoundID soundID;
    AudioServicesCreateSystemSoundID(soundURL, &soundID);

    // Play the sound
    AudioServicesPlaySystemSound(soundID);

    // Wait for the sound to finish playing
    CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0.25, false);

    // Clean up resources
    AudioServicesDisposeSystemSoundID(soundID);
    CFRelease(soundURL);
}
void play_sound_touch(){
    // Specify the path to the audio file
    CFURLRef soundURL = CFURLCreateWithFileSystemPath(NULL, CFSTR("Touch.wav"), kCFURLPOSIXPathStyle, false);

    // Create a system sound ID
    SystemSoundID soundID;
    AudioServicesCreateSystemSoundID(soundURL, &soundID);

    // Play the sound
    AudioServicesPlaySystemSound(soundID);

    // Wait for the sound to finish playing
    CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0.4, false);

    // Clean up resources
    AudioServicesDisposeSystemSoundID(soundID);
    CFRelease(soundURL);
}
void play_sound_page(){
    // Specify the path to the audio file
    CFURLRef soundURL = CFURLCreateWithFileSystemPath(NULL, CFSTR("Page.wav"), kCFURLPOSIXPathStyle, false);

    // Create a system sound ID
    SystemSoundID soundID;
    AudioServicesCreateSystemSoundID(soundURL, &soundID);

    // Play the sound
    AudioServicesPlaySystemSound(soundID);

    // Wait for the sound to finish playing
    CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0.4, false);

    // Clean up resources
    AudioServicesDisposeSystemSoundID(soundID);
    CFRelease(soundURL);
}
void play_sound_Pouringwater(){
    // Specify the path to the audio file
    CFURLRef soundURL = CFURLCreateWithFileSystemPath(NULL, CFSTR("Pouringwater.wav"), kCFURLPOSIXPathStyle, false);

    // Create a system sound ID
    SystemSoundID soundID;
    AudioServicesCreateSystemSoundID(soundURL, &soundID);

    // Play the sound
    AudioServicesPlaySystemSound(soundID);

    // Wait for the sound to finish playing
    CFRunLoopRunInMode(kCFRunLoopDefaultMode, 1, false);

    // Clean up resources
    AudioServicesDisposeSystemSoundID(soundID);
    CFRelease(soundURL);
}
void play_sound_ice(){
    // Specify the path to the audio file
    CFURLRef soundURL = CFURLCreateWithFileSystemPath(NULL, CFSTR("ice.wav"), kCFURLPOSIXPathStyle, false);

    // Create a system sound ID
    SystemSoundID soundID;
    AudioServicesCreateSystemSoundID(soundURL, &soundID);

    // Play the sound
    AudioServicesPlaySystemSound(soundID);

    // Wait for the sound to finish playing
    CFRunLoopRunInMode(kCFRunLoopDefaultMode, 1, false);

    // Clean up resources
    AudioServicesDisposeSystemSoundID(soundID);
    CFRelease(soundURL);
}
void play_sound_powder(){
    // Specify the path to the audio file
    CFURLRef soundURL = CFURLCreateWithFileSystemPath(NULL, CFSTR("powder.wav"), kCFURLPOSIXPathStyle, false);

    // Create a system sound ID
    SystemSoundID soundID;
    AudioServicesCreateSystemSoundID(soundURL, &soundID);

    // Play the sound
    AudioServicesPlaySystemSound(soundID);

    // Wait for the sound to finish playing
    CFRunLoopRunInMode(kCFRunLoopDefaultMode, 1, false);

    // Clean up resources
    AudioServicesDisposeSystemSoundID(soundID);
    CFRelease(soundURL);
}
void play_sound_success(){
    // Specify the path to the audio file
    CFURLRef soundURL = CFURLCreateWithFileSystemPath(NULL, CFSTR("Success.wav"), kCFURLPOSIXPathStyle, false);

    // Create a system sound ID
    SystemSoundID soundID;
    AudioServicesCreateSystemSoundID(soundURL, &soundID);

    // Play the sound
    AudioServicesPlaySystemSound(soundID);

    // Wait for the sound to finish playing
    CFRunLoopRunInMode(kCFRunLoopDefaultMode, 1, false);

    // Clean up resources
    AudioServicesDisposeSystemSoundID(soundID);
    CFRelease(soundURL);
}
void play_sound_fail(){
    // Specify the path to the audio file
    CFURLRef soundURL = CFURLCreateWithFileSystemPath(NULL, CFSTR("Fail.wav"), kCFURLPOSIXPathStyle, false);

    // Create a system sound ID
    SystemSoundID soundID;
    AudioServicesCreateSystemSoundID(soundURL, &soundID);

    // Play the sound
    AudioServicesPlaySystemSound(soundID);

    // Wait for the sound to finish playing
    CFRunLoopRunInMode(kCFRunLoopDefaultMode, 2, false);

    // Clean up resources
    AudioServicesDisposeSystemSoundID(soundID);
    CFRelease(soundURL);
}
void play_sound_time(){
    // Specify the path to the audio file
    CFURLRef soundURL = CFURLCreateWithFileSystemPath(NULL, CFSTR("time.wav"), kCFURLPOSIXPathStyle, false);

    // Create a system sound ID
    SystemSoundID soundID;
    AudioServicesCreateSystemSoundID(soundURL, &soundID);

    // Play the sound
    AudioServicesPlaySystemSound(soundID);

    // Wait for the sound to finish playing
    CFRunLoopRunInMode(kCFRunLoopDefaultMode, 4, false);

    // Clean up resources
    AudioServicesDisposeSystemSoundID(soundID);
    CFRelease(soundURL);
}
void play_sound_paste(){
    // Specify the path to the audio file
    CFURLRef soundURL = CFURLCreateWithFileSystemPath(NULL, CFSTR("paste.wav"), kCFURLPOSIXPathStyle, false);

    // Create a system sound ID
    SystemSoundID soundID;
    AudioServicesCreateSystemSoundID(soundURL, &soundID);

    // Create a separate thread for printing
    pthread_t thread;
    pthread_create(&thread, NULL, printtags, NULL);

    // Play the sound
    AudioServicesPlaySystemSound(soundID);

    // Wait for the sound to finish playing
    CFRunLoopRunInMode(kCFRunLoopDefaultMode, 1, false);
    // Play the sound
    AudioServicesPlaySystemSound(soundID);

    // Wait for the sound to finish playing
    CFRunLoopRunInMode(kCFRunLoopDefaultMode, 1, false);    
    // Play the sound
    AudioServicesPlaySystemSound(soundID);

    // Wait for the sound to finish playing
    CFRunLoopRunInMode(kCFRunLoopDefaultMode, 1, false);
    // Clean up resources
    AudioServicesDisposeSystemSoundID(soundID);
    CFRelease(soundURL);
}
void play_sound_goods(){
    // Specify the path to the audio file
    CFURLRef soundURL = CFURLCreateWithFileSystemPath(NULL, CFSTR("goods.wav"), kCFURLPOSIXPathStyle, false);

    // Create a system sound ID
    SystemSoundID soundID;
    AudioServicesCreateSystemSoundID(soundURL, &soundID);

    // Create a separate thread for printing
    pthread_t thread;
    pthread_create(&thread, NULL, printgoods, NULL);

    // Play the sound
    AudioServicesPlaySystemSound(soundID);

    // Wait for the sound to finish playing
    CFRunLoopRunInMode(kCFRunLoopDefaultMode, 1, false);
    // Play the sound
    AudioServicesPlaySystemSound(soundID);

    // Wait for the sound to finish playing
    CFRunLoopRunInMode(kCFRunLoopDefaultMode, 1, false);    
    // Play the sound
    AudioServicesPlaySystemSound(soundID);

    // Wait for the sound to finish playing
    CFRunLoopRunInMode(kCFRunLoopDefaultMode, 1, false);
    // Clean up resources
    AudioServicesDisposeSystemSoundID(soundID);
    CFRelease(soundURL);
}
void play_sound_Bye(){
    // Specify the path to the audio file
    CFURLRef soundURL = CFURLCreateWithFileSystemPath(NULL, CFSTR("FamilyMart_Ringtone Piano.wav"), kCFURLPOSIXPathStyle, false);

    // Create a system sound ID
    SystemSoundID soundID;
    AudioServicesCreateSystemSoundID(soundURL, &soundID);

    // Create a separate thread for printing
    pthread_t thread;
    pthread_create(&thread, NULL, printBye, NULL);

    // Play the sound
    AudioServicesPlaySystemSound(soundID);

    // Wait for the sound to finish playing
    CFRunLoopRunInMode(kCFRunLoopDefaultMode, 8, false);

    //CFRunLoopRunInMode(kCFRunLoopDefaultMode, 8, false);

    // Clean up resources
    AudioServicesDisposeSystemSoundID(soundID);
    CFRelease(soundURL);
}
void* printRunnung(void* arg){
    for (int i = 0; i < 3; i++){
        printf("🏃🏃🏃🏃🏃🏃");
        fflush(stdout);
        sleep(1); // Adjust the sleep duration as needed            
    }
    return NULL;
}
void* printtags(void* arg){
    for (int i = 0; i < 3; i++){
        printf("🏷️ 🏷️ 🏷️ 🏷️ 🏷️ 🏷️ 🏷️ ");
        if (i == 2) printf("\n");
        fflush(stdout);
        sleep(1); // Adjust the sleep duration as needed            
    }
    return NULL;
}
void* printgoods(void* arg){
    for (int i = 0; i < 3; i++){
        printf("📦📦📦📦📦📦");
        if (i == 2) printf("\n");
        fflush(stdout);
        sleep(1); // Adjust the sleep duration as needed            
    }
    return NULL;
}
void* printBye(void* arg){
   printf("\033[1m"); 
    printf("\033[31mB ");
    fflush(stdout);
    sleep(1); // Adjust the sleep duration as needed           
    printf("\033[32mY ");
    fflush(stdout);
    sleep(1); // Adjust the sleep duration as needed   
    printf("\033[33mE ");
    fflush(stdout);
    sleep(1); // Adjust the sleep duration as needed   
    printf("\033[34m~ ");
    fflush(stdout);
    sleep(1); // Adjust the sleep duration as needed
    printf("\033[35mB ");
    fflush(stdout);
    sleep(1); // Adjust the sleep duration as needed    
    printf("\033[36mY ");
    fflush(stdout);
    sleep(1); // Adjust the sleep duration as needed 
    printf("\033[31mE ");
    fflush(stdout);
    sleep(1); // Adjust the sleep duration as needed
    printf("\033[32m~\033[0m");
    fflush(stdout);
    sleep(1); // Adjust the sleep duration as needed   
    return NULL;
}