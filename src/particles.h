/*import pygame
import math
import random
from . import utils
class particle:
    def __init__(self,center:utils.vector2,rot:float,lifetime:float,from_alpha:float,to_alpha:float,from_scale:float,to_scale:float,dist:float,speed:float,sprite:pygame.Surface):
        self.lifetime = lifetime
        self.lifetime_timer = 0
        self.center = center
        self.pos = center
        self.scale = from_scale
        self.from_scale =from_scale
        self.to_scale =to_scale
        self.rot = rot
        self.alpha= from_alpha
        self.from_alpha = from_alpha
        self.to_alpha = to_alpha
        self.dist = dist
        self.speed = speed
        self.sprite = sprite
    def update(self,dt):
        self.lifetime_timer+=dt
        t = min(1,self.lifetime_timer/self.lifetime)
        self.dist += self.speed*dt
        self.pos = self.center + utils.vector2(math.cos(-self.rot),math.sin(-self.rot))*self.dist
        self.scale = utils.lerp(self.from_scale,self.to_scale,t)
        self.alpha = utils.lerp(self.from_alpha,self.to_alpha,t)
    def draw(self,screen:pygame.Surface,camera_pos:utils.vector2):
        scaled_img = pygame.transform.scale_by(self.sprite,self.scale)
        img = pygame.transform.rotate(scaled_img,math.degrees(self.rot))
        img.set_alpha(self.alpha)
        render_rect = img.get_rect(center = (self.pos-camera_pos).to_tuple())
        screen.blit(img,render_rect)

class range:
    def __init__(self,a,b):
        self.a = a
        self.b = b
    def return_rand_in_range(self):
        return random.uniform(self.a,self.b)
    def return_rand_in_range_int(self):
        return random.uniform(self.a,self.b)*/