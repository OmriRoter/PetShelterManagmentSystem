#ifndef TRAINING_TIPS_DATA_H
#define TRAINING_TIPS_DATA_H

/**
 * @struct TrainingTip
 * @brief Represents a training tip for a specific pet breed and age category.
 */
typedef struct {
    const char* breed;        /**< The breed of the pet */
    const char* ageCategory;  /**< The age category of the pet */
    const char* tips;         /**< The training tips for the pet */
} TrainingTip;

/**
 * @brief Array of training tips for different dog breeds and age categories.
 */
const TrainingTip dogTrainingTips[] = {
    {"Golden Retriever", "Puppy", "Encourage social interactions with humans and pets alike, start 'sit' and 'stay' commands, and discourage nipping with toys."},
    {"Golden Retriever", "Young", "Enhance fetching skills, promote calm leash behavior, and reinforce following commands from a distance."},
    {"Golden Retriever", "Adult", "Strengthen obedience with complex commands, participate in water rescue or agility sports for mental stimulation."},

    {"Labrador", "Puppy", "Emphasize early exposure to water and fetch games, introduce 'drop it' commands, and ensure soft mouth handling."},
    {"Labrador", "Young", "Focus on perfecting fetch techniques, teach 'wait' at doors, and manage dietary habits to prevent obesity."},
    {"Labrador", "Adult", "Engage in tracking games, maintain agility with regular exercise, and focus on steady temperament training."},

    {"German Shepherd", "Puppy", "Prioritize early exposure to varied environments, begin agility training, and enforce discipline with gentle guidance."},
    {"German Shepherd", "Young", "Introduce tasks that challenge their intellect and body, such as advanced tracking and public obedience."},
    {"German Shepherd", "Adult", "Engage in protection sports, reinforce task-oriented exercises, and ensure mental health with problem-solving tasks."},

    {"Bulldog", "Puppy", "Encourage socialization with children and other pets, start with very short walks, and introduce basic hygiene routines."},
    {"Bulldog", "Young", "Focus on breathing exercises, increase endurance gently, and introduce interactive feeding games."},
    {"Bulldog", "Adult", "Regularly monitor health, focus on maintaining mobility with low-stress exercises, and strengthen bonds through gentle play."},

    {"Poodle", "Puppy", "Introduce basic agility tasks, focus on early grooming habituation, and engage in puzzle games for mental growth."},
    {"Poodle", "Young", "Increase complexity in agility courses, practice detailed grooming tasks, and teach music-related commands."},
    {"Poodle", "Adult", "Maintain agility with weekly courses, focus on perfecting grooming, and involve in activities that stimulate their intellect."},

    {"Mixed Breed", "Puppy", "Adapt training based on breed characteristics, encourage robust socialization, and use varied training methods."},
    {"Mixed Breed", "Young", "Customize obedience training to suit unique traits, focus on environmental adaptability, and maintain consistent exercise."},
    {"Mixed Breed", "Adult", "Continue with advanced training sessions, ensure adaptability training continues, and engage in breed-specific activities."}
};

/**
 * @brief Array of training tips for different cat breeds and age categories.
 */
const TrainingTip catTrainingTips[] = {
    {"Siamese", "Kitten", "Focus on agility training, introduce vertical spaces early, and encourage vocal communication."},
    {"Siamese", "Young", "Enhance command training with tricks, introduce leash walking, and use clicker training for positive reinforcement."},
    {"Siamese", "Adult", "Maintain intellectual stimulation with advanced puzzle feeders, engage in regular vocal interactions, and ensure ample climbing spaces."},

    {"Persian", "Kitten", "Gently accustom to grooming, provide serene play environments, and encourage exploring in safe spaces."},
    {"Persian", "Young", "Continue with regular grooming routines, introduce gentle handling by different people, and ensure peaceful resting areas."},
    {"Persian", "Adult", "Maintain coat health with daily brushing, provide calm and enriched environments, and encourage slow-paced games."},

    {"Maine Coon", "Kitten", "Encourage exploration with supervised outdoor access, start grooming early, and introduce water play."},
    {"Maine Coon", "Young", "Continue with outdoor excursions under supervision, increase social interactions, and enhance grooming routines."},
    {"Maine Coon", "Adult", "Maintain physical health with climbing and hunting games, ensure regular vet check-ups for heart health, and provide large water bowls."},

    {"Sphynx", "Kitten", "Acclimate to clothing and bathing routines early, introduce them to various textures, and focus on heat sources."},
    {"Sphynx", "Young", "Maintain skin care routines, introduce structured play times, and ensure warm resting spaces."},
    {"Sphynx", "Adult", "Focus on maintaining skin and dental health, provide consistent warmth, and engage in interactive play sessions."},

    {"Bengal", "Kitten", "Stimulate with high-energy play, start leash training early, and introduce water games."},
    {"Bengal", "Young", "Advance to outdoor adventures on a leash, enhance training with agility tasks, and provide ample climbing structures."},
    {"Bengal", "Adult", "Ensure continuous physical challenges, maintain leash walking, and encourage interactive and stimulating play."},

    {"Mixed Breed", "Kitten", "Tailor training to individual temperament, encourage exploration and climbing, and introduce diverse play items."},
    {"Mixed Breed", "Young", "Adapt training techniques to physical and mental growth, provide varied and stimulating environments, and focus on socialization."},
    {"Mixed Breed", "Adult", "Continue mental stimulation with challenging tasks, maintain regular play routines, and customize care to health needs."}
};

#endif // TRAINING_TIPS_DATA_H