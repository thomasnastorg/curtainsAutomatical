FROM node:13.13.0

RUN mkdir -p /usr/src/app

WORKDIR /usr/src/app

COPY package.json ./

VOLUME ["/usr/src/app"]

RUN npm install

COPY . ./b

EXPOSE 3000

CMD ["npm", "start"]