// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//





#include <iostream>
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <Wmcodecdsp.h>
#include <combaseapi.h>
#include <mferror.h>
#include <tchar.h>
#include <evr.h>
#include<mfobjects.h>

int main()
{
    HRESULT hr = CoInitialize(NULL);

    if (FAILED(hr)) {
        std::cout << "cannot initilize COM";
    }

   
   
        // Initialize the Media Foundation platform.
  hr=     MFStartup(MF_VERSION);

  if (FAILED(hr)) {
      std::cout << "cannot initilize MF";
  }
      
            MF_OBJECT_TYPE ObjectType = MF_OBJECT_INVALID;
            IMFSourceResolver* pSourceResolver;
            IUnknown* pSource = nullptr;
            IMFMediaSource* mSource;
            IMFPresentationDescriptor* ppPresentationDescriptor;
            IMFTransform* mtransform = NULL;
            IMFTopology* topology = NULL;
            IMFStreamDescriptor* sdesip = NULL;
            IMFTopologyNode* source = NULL;
            IMFTopologyNode* transform;
            IMFTopologyNode* output = NULL;
            IMFMediaSink* mediasink = NULL;
            IMFMediaTypeHandler* mediatypehandler;
            IMFMediaType* mediatype;
            IMFMediaType* decodermediatype;
            IMFMediaSession* mediasession;
            DWORD streamdesip;

   hr =      MFCreateSourceResolver(&pSourceResolver);

   if (FAILED(hr)) {
       std::cout << "cannot create source resolver";
   }


   hr = MFCreateTopology(
       &topology
   );

   if (FAILED(hr)) {
       std::cout << "topology";
   }
           

      hr =    pSourceResolver->CreateObjectFromURL(
                L"song.mp3",                       // URL of the source.
                MF_RESOLUTION_MEDIASOURCE,  // Create a source object.
                NULL,                       // Optional property store.
                &ObjectType,     // Receives the created object type. 
                &pSource          // Receives a pointer to the media source.
            );
         
      if (FAILED(hr)) {
          std::cout << "media source";
      }
         hr =  pSource->QueryInterface(IID_PPV_ARGS(&mSource));

         if (FAILED(hr)) {
             std::cout << "media source interface";
         }



      hr =      mSource->CreatePresentationDescriptor(&ppPresentationDescriptor);

      if (FAILED(hr)) {
          std::cout << "presentation discriptor";
      }

    

      BOOL value;
      hr = ppPresentationDescriptor->GetStreamDescriptorByIndex(0, &value, &sdesip);
      if (FAILED(hr)) {
          std::cout << "stream desciption get";
      }

      sdesip->GetStreamIdentifier(&streamdesip);

      hr = sdesip->GetMediaTypeHandler(&mediatypehandler);

      if (FAILED(hr)) {
          std::cout << "media handler";
      }

      hr = mediatypehandler->GetCurrentMediaType(&mediatype);

      if (FAILED(hr)) {
          std::cout << "current media type";
      }


      hr = MFCreateTopologyNode(MF_TOPOLOGY_SOURCESTREAM_NODE, &source);

      if (FAILED(hr)) {
          std::cout << "source topology node";
      }

    

     

       hr =     source->SetUnknown(MF_TOPONODE_SOURCE, mSource);

       if (FAILED(hr)) {
           std::cout << "source set to topology node";
       }
         hr =   source->SetUnknown(MF_TOPONODE_PRESENTATION_DESCRIPTOR, ppPresentationDescriptor);

         if (FAILED(hr)) {
             std::cout << "desciption set to topology node";
         }
          
         hr = source->SetUnknown(MF_TOPONODE_STREAM_DESCRIPTOR, sdesip);

         if (FAILED(hr)) {
             std::cout << "set stream desiptor";
         }

      hr =      topology->AddNode(source);

      if (FAILED(hr)) {
          std::cout << "add source node";
      }

    

            IMFActivate* active;


           hr =  MFCreateAudioRendererActivate(&active);

          if (FAILED(hr)) {
              
              std::cout << "active object";
          }

         
        
          

        hr =     active->ActivateObject(__uuidof(IMFMediaSink), (void**)&mediasink);


        if (FAILED(hr)) {
           
            std::cout << "media sink";
        }
           
           
      

     

      IMFStreamSink* streamsink;

     hr  =  mediasink->GetStreamSinkByIndex(0, &streamsink);

     if (FAILED(hr)) {

         std::cout << "get stream sink";
     }



     hr = MFCreateTopologyNode(MF_TOPOLOGY_OUTPUT_NODE, &output);

     if (FAILED(hr)) {

         std::cout << "output node topology";
     }
   hr =    output->SetObject(streamsink);

   if (FAILED(hr)) {

       std::cout << "set out put node";
   }

   
         
       hr =     topology->AddNode(output);
       if (FAILED(hr)) {

           std::cout << "add topo node output";
       }

     hr =   source->ConnectOutput(0, output, 0);

     if (FAILED(hr)) {

         std::cout << "connect source";
     }

   

  hr =          MFCreateMediaSession(
                NULL,
                &mediasession
            );

  if (FAILED(hr)) {

      std::cout << "create media session";
  }
 hr = mediasession->SetTopology(0, topology);
 if (FAILED(hr)) {

     std::cout << "fail to set topology";
 }



 IMFMediaEvent* mediaevent;

 mediasession->GetEvent(0, &mediaevent);
 MediaEventType Type = MEUnknown;
 mediaevent->GetType(&Type);


 if (Type == 101) {

     std::cout << "helloworld";
 }

 std::cout << "Event: " << Type << std::endl;

            PROPVARIANT var;
            PropVariantInit(&var);
            var.vt = VT_I8;
            var.hVal.QuadPart =0;

            

       hr =      mediasession->Start(&GUID_NULL, &var);

     

       if (FAILED(hr)) {

           std::cout << "media session start";
       }


       int x = 0;

       std::cin >> x;
          pSourceResolver->Release();
            pSource->Release();
            mSource->Release();
           ppPresentationDescriptor->Release();
          
           topology->Release();
           sdesip->Release();
           source->Release();
           
          output->Release();
           mediatypehandler->Release();
            mediatype->Release();
         
         
            mediasession->Release();
            mediasink->Release();

            MFShutdown();

        
        CoUninitialize();
        }
    

