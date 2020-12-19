#ifndef ANIMAL_H
#define ANIMAL_H


#include <graph/entity.h>
#include <graph/type/base.h>
#include <graph/type/buffer.h>

// a species lives in a biome
// a species is herbivor or carnivour

// When we look at our planet as a resource, we can see that there are two
// kinds of animals. Vertebrates and invertebrates. Those with and without
// a backbone. Vertebrates are further broken into mammals, fish, birds,
// amphibians, and reptiles. Invertebrates are broken into annelid worms
// (earthworm, ect.), arthropods (arachnids, crustaceans, insects, myriapods),
// echinoderms (starfish, ect.), eterates (jellyfish, ect.), flatworms,
// mollusks, and protozoa.


// How big is it? Does it have fur, scales, or feathers? Does it have ears?
// Can you see its teeth? How fast is it? What does this animal eat? Is it a
// carnivore, herbivore, or omnivore? How does it hunt (if it hunts)? Does it
// hibernate and store food for the winter? Consider this animal’s habitat.
// This will have a lot to say about its appearance. For example, animals
// that live in the desert usually have developed certain ways of conserving
// water, like a camel with its hump. Is this animal domesticated? Why did
// people decide to domesticate this animal? For example, dogs were domesticated
// to guard a camp, and cats were domesticated to keep vermin away. Has this
// relationship evolved over time?

namespace nature {
  namespace fauna {

    class Species : public graph::Entity {
        enum Diet : std::uint8_t {
          Herbivore,
          Carnivore,
          Omnivore
        };


        // mass - infant adolesance mature elderly
        // height
        // teeth

        // Diet
        //======================
        //The three diets of animals include creatures that eat only plants,
        // those that eat only meat, and animals that eat both plants and meat.
        // Animals that eat plants exclusively are herbivores, and animals that
        // eat only meat are carnivores. When animals eat both plants and meat,
        // they are called omnivores.

        // Gestation Period
        //=====================
        // The gestation period, varies greatly from species to species;
        // it is 40 weeks in humans, 56–60 in giraffes and 16 days in hamsters.
        // Generally, there are two main factors that contribute to the length of
        // the gestation period:
        //
        // Animal size / mass – larger animals tend to have longer gestation periods
        // (as they tend to produce larger offspring). The level of development at birth
        // – more developed infants will typically require a longer gestation period
        //
        // The level of development at birth for mammalian infants can be described as
        // either atricial or precocial. Altricial mammals give birth to relatively helpless,
        // undeveloped offspring that need extended rearing. Precocial mammals give birth to
        // more developed offspring that are mobile and independent and require minimal rearing
        // Generally, altricial mammals (e.g. marsupials and rodents) require shorter gestation
        // periods than precocial mammals (e.g. ungulates such as cows, pigs and rhinoceroses)
        // While the length of a gestation period does appear to positively correlate with size
        // and development, other factors also exist

        // BMI
        //=============================
        // Body Mass Index
        // m	=	mass (in kilograms)
        // h	=	height (in meters)
        //
        // BMI = m/h^2


        // Brain to Body Mass Ratio
        //=============================
        // It is a trend that the larger the animal gets, the smaller the brain-to-body mass ratio
        // is. Large whales have very small brains compared to their weight, and small rodents like
        // mice have a relatively large brain, giving a brain-to-body mass ratio similar to humans.
        // One explanation could be that as an animal's brain gets larger, the size of the neural
        // cells remains the same, and more nerve cells will cause the brain to increase in size to
        // a lesser degree than the rest of the body. This phenomenon can be described by an equation
        // of the form E = CS^r, where E and S are brain and body weights, r a constant that depends
        // on animal family (but close to 2/3 in many vertebrates), and C is the cephalization factor.
        // It has been argued that the animal's ecological niche, rather than its evolutionary family,
        // is the main determinant of its encephalization factor C.[16]
        //
        // small ants	1:7
        // small birds	1:12
        // mouse	1:40
        // human	1:40
        // cat	1:100
        // dog	1:125
        // frog	1:172
        // lion	1:550
        // elephant	1:560
        // horse	1:600
        // shark	1:2496
        // hippopotamus	1:2789


    };


    // define a function that creates the Species Type



  }
}


/*
 *
My bestiary involves taking real-world animals, giving them metaphorical steroids,
and putting some sort of modifier in front of their name. I have greatbears,
broadsheep (these are the least like their real-world counterparts, resembling buffalo),
farwolves, duskrats, ringfoxes, and others. My only notable original flora is a plant
called breakroot, used to make a tribal tea of an opaque white appearance.

It's not the most original way to create flora and fauna, but I use it because it allows
the reader a way to quickly imagine what these creatures look like without having to
spend a paragraph describing them each time one lumbers along. We all know what a bear is.
A greatbear then is pretty easy to imagine. I don't think of it as cheating, I think of it
as comfortable and accessible.


What domesticated animals were pets in your story world? Did they have pets?

What domesticated or wild animals were used for food or on farms?

What wild animals, dangerous, or magical animals roamed their world?

What kind of insects did they have?

What aquatic animals did they have?

What animals were endangered or held sacred?

Did they have sanctuaries, reserves, or zoos?

Did they have legal or illegal hunting or trading?

Did they worship any animal?

Did they have any myths or legends surrounding animals?

Did they have dinosaurs or know about them?

Have you invented Fantasy, magical, or futuristic animals?
*/


#endif // ANIMAL_H
